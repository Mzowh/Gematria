#include "GematriaHTMLBuilder.H++"
#include "Cyphers/All.H++"
#include <fstream>
#include <iostream>

GematriaHTML::GematriaCSS CreateLightTheme() {
	GematriaHTML::GematriaCSS css{};
	css["*"] = {
		"font-family: Arial;"
			"color: darkblue;"
		"width: 65%; margin: auto;"
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

GematriaHTML::GematriaCSS CreateDarkTheme() {
	GematriaHTML::GematriaCSS css{};
	css["*"] = {
		"font-family: Arial;"
		"color: orange;"
		"background-color: black;"
		"width: 50%; margin: auto;"
	};

	css["td"] += {
		"border: 2px solid blue;"
		"text-align: center;"
		"background-color: black;"
	};
	return css;
}
void OutputGematriaToHTML(const Gematria &gematria, std::ofstream &file) {
	std::stringstream stream;
	GematriaHTML::OutputGematriaHTML(gematria, CreateLightTheme(), stream);
	file << stream.str();
}

int main() {
	Gematria gematria;
	gematria.GetCypher() = Cyphers::Jewish();
	std::ifstream input_file("GematriaMain.txt");
	if (!input_file) {
		std::cerr << "Please Create a file named GematriaMain.txt, this will be your input file.";
		return 1;
	}
	GematriaInsertPhrasesStream(gematria, input_file);
	// Output to file "GeneratedSite.html", can be opened with a web browser
	if (std::ofstream output("GeneratedSite.html"); output) {
		OutputGematriaToHTML(gematria, output);
	} else {
		std::cerr << "Cannot write to GeneratedSite.html" << '\n';
	}
	return 0;
}
