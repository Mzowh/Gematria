#include "Simple.H++"

Gematria::CypherMap Cyphers::Simple() {
	Gematria::CypherMap cypher{};
	for (Gematria::PhraseValue value = 1; const char ch : "abcdefghijklmnopqrstuvwxyz") {
		cypher[ch] = value;
		++value;
	}
	return cypher;
}
