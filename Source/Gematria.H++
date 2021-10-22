#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

std::string OptimizePhrase(const std::string &phrase);

class Cypher {
public:
	using Name = std::string;
	using Value = long long;
	using ValueMap = std::map<char, Value>;

	constexpr std::string_view GetName() const {
		return name;
	}
	Value CalculatePhraseValue(const std::string_view phrase);
	constexpr auto &Values() { return values; }
	constexpr const auto &Values() const { return values; }

	explicit Cypher(const Name &name = "Unnamed Cypher", const std::map<char, Value> &values = {});

private:
	Name name;
	std::map<char, Value> values;
	std::map<std::string, Value> optimized_string_to_value;
};

struct GematriaResult {
	std::string phrase;
	Cypher::Value value_singular;
	std::map<Cypher::Name, Cypher::Value> values_all;
	std::vector<std::string> comments;
};

class GematriaSingular {
public:
	void EnterPhrase(const std::string &phrase);

	constexpr const auto &GetPhraseToValue() const {
		return phrase_to_value;
	}

	constexpr const auto &GetValueToPhrases() const {
		return value_to_phrases;
	}

	constexpr const auto &GetCypher() const {
		return cypher;
	}

	constexpr auto &GetCypher() {
		return cypher;
	}

private:
	Cypher *cypher = nullptr;
	std::map<Cypher::Value, std::vector<GematriaResult>> value_to_phrases;
	std::map<std::string, Cypher::Value> phrase_to_value;
	std::set<std::string> entered_phrases;
};


class GematriaMultimap {
public:
	void EnterPhrase(const std::string &phrase, Cypher &cypher);

	template<typename ...Cyphers>
	void EnterPhrase(const std::string &phrase, Cyphers &...cypher) {
		(EnterPhrase(phrase, cypher), ...);
	}

	constexpr const auto &GetResults() const {
		return results;
	}

	constexpr const auto &GetUsedCyphers() const {
		return used_cyphers;
	}

	constexpr const auto &GetEnteredPhrases() const {
		return entered_phrases;
	}

	const std::string &GetOptimizedPhrase(const std::string &phrase) const;

private:
	std::map<std::string, GematriaResult> results;
	std::map<std::string, std::string> phrase_to_optimized;
	std::set<std::string> used_cyphers;
	std::set<std::string> entered_phrases;
};

// Map of Cypher Names to Cyphers
using CypherMap = std::map<std::string, Cypher>;
