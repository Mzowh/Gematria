#include "Mzowh.H++"

Gematria::CypherMap Cyphers::Mzowh() {
	Gematria::CypherMap cypher{};
	cypher['a'] = 1;
	for (const auto c : "bcd") cypher[c] = 4;
	for (const auto c : "efgh") cypher[c] = 8;
	for (const auto c : "ijklmn") cypher[c] = 5;
	for (const auto c : "opqrst") cypher[c] = 2;
	for (const auto c : "uvwxyz") cypher[c] = 8;
	return cypher;
}

Gematria::CypherMap Cyphers::Mzowh_Multiplicative() {
	Gematria::CypherMap cypher{};
	cypher['a'] = 1;
	for (const auto c : "bcd") cypher[c] = 3;
	for (const auto c : "efgh") cypher[c] = 3;
	for (const auto c : "ijklmn") cypher[c] = 9;
	for (const auto c : "opqrst") cypher[c] = 6;
	for (const auto c : "uvwxyz") cypher[c] = 9;
	return cypher;
}

Gematria::CypherMap Cyphers::New() {
	Gematria::CypherMap cypher{};
	cypher['a'] = 10;
	cypher['b'] = 3;
	cypher['c'] = 8;
	cypher['d'] = 11;
	cypher['e'] = 14;
	cypher['f'] = 33;
	cypher['g'] = 61;
	cypher['h'] = 91;
	cypher['i'] = 17;
	cypher['j'] = 18;
	cypher['k'] = 20;
	cypher['l'] = 30;
	cypher['m'] = 100;
	cypher['n'] = 48;
	cypher['o'] = 43;
	cypher['p'] = 34;
	cypher['q'] = 200;
	cypher['r'] = 140;
	cypher['s'] = 250;
	cypher['t'] = 88;
	cypher['u'] = 6;
	cypher['v'] = 9;
	cypher['w'] = 12;
	cypher['x'] = 15;
	cypher['y'] = 25;
	cypher['z'] = 35;
	return cypher;
}
