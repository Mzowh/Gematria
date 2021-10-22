#include "Gematria.H++"
#include <algorithm>
#include <functional>

Cypher::Value Cypher::CalculatePhraseValue(const std::string_view phrase) {
	if (const auto iter = optimized_string_to_value.find(phrase.data()); iter != optimized_string_to_value.end()) {
		return iter->second;
	} else {
		Value value = 0;
		for (const char character : phrase)
			value += values.at(character);
		optimized_string_to_value[phrase.data()] = value;
		return value;
	}
}

Cypher::Cypher(const Name &name, const std::map<char, Value> &values) : name(name), values(values) {
}

std::string OptimizePhrase(const std::string &phrase) {
	std::string optimization = phrase;
	// Sort the phrase alphabetically, for optimization.Letters are together in ASCII, making the branch predictor go BRRR
	std::sort(optimization.begin(), optimization.end(), std::less<char>{});
	// For the sorted phrase, Erase digits, punctuation, and spaces
	optimization.erase(std::remove_if(optimization.begin(), optimization.end(), [&](const char ch) {
		return std::isdigit(ch) || std::isspace(ch) || std::ispunct(ch);
		}), optimization.end());
	// If the value is alphabetical, ensure that the input is lower case
	for (auto &ch : optimization) if (std::isalpha(ch) && isupper(ch)) ch = std::tolower(ch);
	std::sort(optimization.begin(), optimization.end(), std::less<char>{});
	return optimization;
}

void GematriaMultimap::EnterPhrase(const std::string &phrase, Cypher &cypher) {
	const std::string optimized = OptimizePhrase(phrase);
	const auto value = cypher.CalculatePhraseValue(optimized);
	const std::string cypher_name(cypher.GetName());
	auto &result = results[phrase];
	result.values_all[cypher_name] = value;
	phrase_to_optimized[phrase] = optimized;
	used_cyphers.emplace(cypher_name);
	entered_phrases.emplace(cypher_name);
}

const std::string &GematriaMultimap::GetOptimizedPhrase(const std::string &phrase) const {
	return phrase_to_optimized.at(phrase);
}

void GematriaSingular::EnterPhrase(const std::string &phrase) {
	if (entered_phrases.contains(phrase)) return;
	const std::string optimization = OptimizePhrase(phrase);
	const auto value = cypher->CalculatePhraseValue(optimization);
	GematriaResult result;
	result.phrase = phrase;
	result.value_singular = value;
	value_to_phrases[value].push_back(result);
	phrase_to_value[phrase] = value;
	entered_phrases.emplace(phrase);
}
