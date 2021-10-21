#include "Gematria.H++"
#include <algorithm>
#include <fstream>
#include <set>
#include <iostream>

// Used to prevent a loop of included files
std::set<std::string> IncludedFiles;

void Gematria::CondenseString(String &string) const {
	// Sort the phrase alphabetically,for optimization. Letters are together in ASCII, making the branch predictor go BRRR
	std::sort(string.begin(), string.end(), std::less<Character>{});
	// For the sorted phrase, Erase digits, punctuation, and spaces
	string.erase(std::remove_if(string.begin(), string.end(), [&](const Character ch) {
		return std::isdigit(ch) || std::isspace(ch) || std::ispunct(ch);
		}), string.end());
	// If the value is alphabetical, ensure that the input is lower case
	for (auto &ch : string) if (std::isalpha(ch) && isupper(ch)) ch = std::tolower(ch);
	// Get rid of non-cypher values
	string.erase(std::remove_if(string.begin(), string.end(), [&](const Character ch) {
		return !cypher.contains(ch);
		}), string.end());

	/// Sort for the final time
	std::sort(string.begin(), string.end(), std::less<Character>{});
}

Gematria::Result Gematria::ComputePhraseResult(const PhraseView phrase) const {
	// We sort the original phrase into an optimized version, so that look-up times are swift
	Gematria::Result result{ String(phrase), String(phrase), 0 };
	auto &[original, sorted_phrase, value, special] = result;
	// if the string has already been optimized, return it. (A secret weapon!)
	[[likely]] if (const auto unoptimized_phrase_iter = unoptimized_string_map.find(sorted_phrase); unoptimized_phrase_iter != unoptimized_string_map.end()) {
		const auto [key, optimization] = *unoptimized_phrase_iter;
		// Second is the phrase value
		value = optimization->second;
		return result;
	}

	// Optimize the string
	CondenseString(sorted_phrase);
	result.value = ComputePhraseGematriaValue(sorted_phrase);
	return result;
}

void Gematria::EnterPhrase(const PhraseView original_phrase) {
	EnterResult(ComputePhraseResult(original_phrase));
}

void Gematria::EnterPhrase(const PhraseView phrase, const Special &special) {
	Result result = ComputePhraseResult(phrase);
	result.special = special;
	EnterResult(result);
}

Gematria::PhraseValue Gematria::ComputePhraseGematriaValue(const PhraseView phrase) const {
	PhraseValue value = 0;
	for (const auto ch : phrase) {
		const auto at = cypher.at(ch);
		value += at;
	}
	return value;
}

void Gematria::EnterResult(const Result &result) {
	// Do not allow repeated entries
	if (unoptimized_string_map.contains(result.original))
		return;

	// Insert the sorted phrase into the optimizer, along with its phrase value, so that it can be quickly found later
	const auto [optimization, inserted] = phrase_to_value.insert_or_assign(result.original, result.value);
	// Add the cache into the phrase map
	value_to_phrases[result.value].emplace_back(result);
	unoptimized_string_map.emplace(result.original, optimization);
	unoptimized_string_to_special_map.emplace(result.original, result.special);
}

bool Gematria::IsResultValid(const Result &result) const {
	return ComputePhraseResult(result.optimization).value == result.value;
}

void GematriaInsertPhrasesStream(Gematria &gematria, std::istream &stream, const Gematria::Character delimiter) {
	constexpr std::string_view Command_Comment = "@Comment ";
	constexpr std::string_view Command_DocName = "@DocName ";
	constexpr std::string_view Command_Include = "@Include ";

	Gematria::String line;
	Gematria::Special special;
	Gematria::String doc_name;

	const auto IsComment = [&]() {
		return line.size() > Command_Comment.size() && line.substr(0, Command_Comment.size()) == Command_Comment;
	};

	const auto IsDocName = [&]() {
		return line.size() > Command_DocName.size() && line.substr(0, Command_DocName.size()) == Command_DocName;
	};


	const auto IsInclude = [&]() {
		return line.size() > Command_Include.size() && line.substr(0, Command_Include.size()) == Command_Include;
	};

	while (stream) {
		std::getline(stream, line, '\n');
		if (line.empty()) continue;

		if (IsDocName()) {
			doc_name =  "[" + line.substr(Command_DocName.size(), line.size() - Command_DocName.size()) + "] ";
		} else if (IsComment()) {
			special.comment = line.substr(Command_Comment.size(), line.size() - Command_Comment.size());
		} else if (IsInclude()) {
			const auto included_file = line.substr(Command_Include.size(), line.size() - Command_Include.size());
			if (!IncludedFiles.contains(included_file)) {
				// Create a file stream and ensure the file exists
				std::ifstream file_stream(included_file);
				if (file_stream) {
					GematriaInsertPhrasesStream(gematria, file_stream);
					IncludedFiles.emplace(included_file);
				} else {
					std::cerr << "Unable to read " << included_file << '\n';
				}
			}
		} else {
			auto result = gematria.ComputePhraseResult(line);
			result.special = std::move(special);
			result.special.comment = doc_name + result.special.comment;
			gematria.EnterResult(result);
		}
	}
}

void CombineCyphers(Gematria::CypherMap &left, const Gematria::CypherMap &right) {
	for (auto &[key, value] : right) {
		left[key] = value;
	}
}

void CombineCyphersAdd(Gematria::CypherMap &left, const Gematria::CypherMap &right) {
	for (auto &[key, value] : left) {
		if (right.contains(key)) {
			left[key] += right.at(key);
		}
	}
}

void CombineCyphersSubtract(Gematria::CypherMap &left, const Gematria::CypherMap &right) {
	for (auto &[key, value] : left) {
		if (right.contains(key)) {
			left[key] -= right.at(key);
		}
	}
}

void CombineCyphersMultiply(Gematria::CypherMap &left, const Gematria::CypherMap &right) {
	for (auto &[key, value] : left) {
		if (right.contains(key)) {
			left[key] *= right.at(key);
		}
	}
}
