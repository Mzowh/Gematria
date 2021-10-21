#pragma once
#pragma once
#include <map>
#include <string>
#include <vector>
#include <variant>
#include <istream>

class Gematria {
public:
	using Character = char;
	using PhraseValue = long long;
	using CypherMap = std::map<Character, PhraseValue>;
	using String = std::basic_string<Character>;
	using Phrase = String;
	using PhraseView = std::basic_string_view<Character>;
	using CondensedStringView = std::basic_string_view<Character>;
	using PhraseToValueMap = std::map<Phrase, PhraseValue>;
	using UnoptimizedStringToPhraseMap = std::map<Phrase, PhraseToValueMap::iterator>;

	// Special information entered by the user for the result
	struct Special {
		String comment;
	};

	using UnoptimizedPhraseToSpecialMap = std::map<Phrase, Special>;

	struct Result {
		String original;
		String optimization;
		PhraseValue value;
		Special special;
	};

	using Caches = std::vector<Result>;
	using ValueToPhrasesMap = std::map<PhraseValue, Caches>;
protected:
	// Stores the conversion between a character and a value
	CypherMap cypher;
	// Stores the computed result of each phrase
	ValueToPhrasesMap value_to_phrases;
	PhraseToValueMap phrase_to_value;
	UnoptimizedStringToPhraseMap unoptimized_string_map;
	UnoptimizedPhraseToSpecialMap unoptimized_string_to_special_map;

public:
	constexpr CypherMap &GetCypher() {
		return cypher;
	}
	constexpr const CypherMap &GetCypher() const {
		return cypher;
	}
	constexpr const ValueToPhrasesMap &GetPhraseResultsMap() const {
		return value_to_phrases;
	}
	constexpr const UnoptimizedPhraseToSpecialMap &GetSpecialsMap() const {
		return unoptimized_string_to_special_map;
	}

	// Optimizes a string for fast querying
	void CondenseString(String &string) const;
	// Returns a structure containing the original phrase, its optimization, and its gematria value.
	// Normally used in conjunction with fn EnterResult
	Result ComputePhraseResult(const PhraseView phrase) const;
	// Enters a phrase into the result map
	void EnterPhrase(const PhraseView phrase);
	// Enter a phrase into the result map with a special value included
	void EnterPhrase(const PhraseView phrase, const Special &special);
	// Enters a result into the result map (Does not validate)
	void EnterResult(const Result &result);
	// Validates a result, for error checking
	bool IsResultValid(const Result &result) const;
	// Computes the gematria value of a standalone phrase
	PhraseValue ComputePhraseGematriaValue(const PhraseView phrase) const;
};

// Insert phrases from a stream, line by line
void GematriaInsertPhrasesStream(Gematria &gematria, std::istream &stream, const Gematria::Character delimiter = '\n');
void CombineCyphers(Gematria::CypherMap &left, const Gematria::CypherMap &right);
void CombineCyphersAdd(Gematria::CypherMap& left, const Gematria::CypherMap& right);
void CombineCyphersSubtract(Gematria::CypherMap& left, const Gematria::CypherMap& right);
void CombineCyphersMultiply(Gematria::CypherMap& left, const Gematria::CypherMap& right);
