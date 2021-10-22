#include "Gematria.H++"
#include "GematriaHTMLBuilder.H++"
#include <fstream>

GematriaHTML::GematriaCSS CreateLightTheme() {
	GematriaHTML::GematriaCSS css{};
	css["*"] = {
		"font-family: Arial;"
			"color: darkblue;"
			"text-align: center;"
	};

	css["div"] = {
			"width: 50%; margin: auto;"
	};


	css["table"] = {
			"width: 50%; margin: auto;"
	};

	css["td"] = {
		"border: 2px solid blue;"
			"text-align: center;"
			"background-image: linear-gradient(white, yellow);"
	};
	css["th"] = {
		"border: 2px solid blue;"
			"text-align: center;"
			"background-image: linear-gradient(white, blue);"
	};
	return css;

}

GematriaHTML::GematriaCSS CreateWoodTheme() {
	GematriaHTML::GematriaCSS css{};
	css["*"] = {
		"font-family: Times New Roman;"
			"color: black;"
			"text-align: center;"
	};

	css["div"] = {
			"width: 50%; margin: auto;"
	};


	css["table"] = {
			"width: 50%; margin: auto;"
			"border-collapse:collapse;"

	};

	css["body"] = {
			"background-image: url(\"CSS/wood2.jpg\");"
	};

	css["td"] = {
			"text-align: center;"
			"background-image: url(\"CSS/paper.jpg\");"
			"border: 1px solid grey;"
	};
	css["th"] = {
			"text-align: center;"
			"background-image: url(\"CSS/wood.jpg\");"
			"border: 1px solid black;"
	};
	return css;

}

const auto EnglishOrdinalCypher = []() {
	Cypher::ValueMap map;
	for (Cypher::Value value = 1; const char ch : "abcdefghijklmnopqrstuvwxyz") {
		map[ch] = value;
		++value;
	}
	return Cypher("English Ordinal", map);
};


const auto EnglishOrdinalReversedCypher = []() {
	Cypher::ValueMap map;
	for (Cypher::Value value = 26; const char ch : "abcdefghijklmnopqrstuvwxyz") {
		map[ch] = value;
		--value;
	}
	return Cypher("English Ordinal Reversed", map);
};

const auto JewishCypher = []() {
	Cypher::ValueMap map;
	map['a'] = 1;
	map['b'] = 2;
	map['c'] = 3;
	map['d'] = 4;
	map['e'] = 5;
	map['f'] = 6;
	map['g'] = 7;
	map['h'] = 8;
	map['i'] = 9;
	map['j'] = 600;
	map['k'] = 10;
	map['l'] = 20;
	map['m'] = 30;
	map['n'] = 40;
	map['o'] = 50;
	map['p'] = 60;
	map['q'] = 70;
	map['r'] = 80;
	map['s'] = 90;
	map['t'] = 100;
	map['u'] = 200;
	map['v'] = 700;
	map['w'] = 900;
	map['x'] = 300;
	map['y'] = 400;
	map['z'] = 500;
	return Cypher("Jewish", map);
};

const auto MzowhCypher = []() {
	Cypher::ValueMap map;
	map['a'] = 1;
	for (const auto c : "bcd") map[c] = 4;
	for (const auto c : "efgh") map[c] = 8;
	for (const auto c : "ijklmn") map[c] = 5;
	for (const auto c : "opqrst") map[c] = 2;
	for (const auto c : "uvwxyz") map[c] = 8;
	return Cypher("Mzowh", map);
};

const auto MzowhCypherReversed = []() {
	Cypher::ValueMap map;
	map['a'] = 8;
	for (const auto c : "bcd") map[c] = 2;
	for (const auto c : "efgh") map[c] = 5;
	for (const auto c : "ijklmn") map[c] = 8;
	for (const auto c : "opqrst") map[c] = 4;
	for (const auto c : "uvwxyz") map[c] = 1;
	return Cypher("Mzowh Reversed", map);
};

const auto EnglishCypher = []() {
	Cypher::ValueMap map;
	for (Cypher::Value value = 6; const char ch : "abcdefghjijklmnopqrstuvwxyz") {
		map[ch] = value;
		value += 6;
	}
	return Cypher("English", map);
};

GematriaMultimap gematria_multiple;
auto mzowh = MzowhCypher();
auto mzowh_reversed = MzowhCypherReversed();
auto english = EnglishCypher();
auto english_ordinal = EnglishOrdinalCypher();
auto english_ordinal_reversed = EnglishOrdinalReversedCypher();
auto jewish = JewishCypher();

std::vector<GematriaSingular *> listeners;

GematriaSingular gematria_mzowh;
GematriaSingular gematria_mzowh_reversed;
GematriaSingular gematria_english;
GematriaSingular gematria_english_ordinal;
GematriaSingular gematria_english_ordinal_reversed;
GematriaSingular gematria_jewish;

void GematriaReadFile(std::istream&& file, const char delimiter = '\n') {
	if (!file)
		return;
	std::string line;
	while (std::getline(file, line, delimiter)) {
		if (!line.empty()) {
			gematria_multiple.EnterPhrase(line, mzowh, mzowh_reversed, english, english_ordinal, english_ordinal_reversed, jewish);
			for (auto &listener : listeners) {
				listener->EnterPhrase(line);
			}
			line.clear();
		}
	}
}

int main() {
	gematria_mzowh.GetCypher() = &mzowh;
	gematria_mzowh_reversed.GetCypher() = &mzowh_reversed;
	gematria_english.GetCypher() = &english;
	gematria_english_ordinal.GetCypher() = &english_ordinal;
	gematria_english_ordinal_reversed.GetCypher() = &english_ordinal_reversed;
	gematria_jewish.GetCypher() = &jewish;
	listeners = { &gematria_mzowh, &gematria_mzowh_reversed, &gematria_english, &gematria_english_ordinal, &gematria_english_ordinal_reversed, &gematria_jewish };
	
	GematriaReadFile(std::ifstream("GematriaMain.txt"));

	std::ofstream output("Test.html");
	GematriaHTML::Begin(output);
	GematriaHTML::Head(CreateWoodTheme(), output);
	GematriaHTML::MultiMapBody(gematria_multiple, output);
	for (const auto listener : listeners) {
		GematriaHTML::SingularBody(*listener, output);
	}

	GematriaHTML::End(output);
	return 0;
}
