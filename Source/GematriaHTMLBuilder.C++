#include "GematriaHTMLBuilder.H++"

// Generates HTML for a Single Gematria instance

void GematriaHTML::MultiMapBody(const GematriaMultimap &gematria, std::ostream &s) {
	const auto &results = gematria.GetResults();
	const auto &cyphers = gematria.GetUsedCyphers();
	const auto &phrases = gematria.GetEnteredPhrases();

	s << "<h3>All listings</h3>";

	// Generate the table which combines all of the results
	// Show cyphers used
	s << "<table>";
	s << "<tr><th>Phrase</th>";
	for (const auto &cypher : cyphers)
		s << "<th>" << cypher << "</th>";
	s << "</tr>";

	for (const auto &[phrase, result] : results) {
		s << "<tr>";
		s << "<td>" << phrase << "</td>";
		for (const auto &cypher : cyphers) {
			// If the phrase used the cypher, include it
			if (const auto iter = result.values_all.find(cypher); iter != result.values_all.end()) {
				s << "<td>" << iter->second << "</td>";
			} else {
				// This phrase did not use the cypher
				s << "<td>???</td>";
			}
		}
	}

	s << "</table>";
}

void GematriaHTML::SingularBody(const GematriaSingular &gematria, std::ostream &s) {
	const auto &value_to_phraes = gematria.GetValueToPhrases();
	s << "<h3>" << gematria.GetCypher()->GetName() << " listings</h3>";
	for (const auto &[value, results] : value_to_phraes) {
		s << "<table><th>Phrase</th><th>Value</th>";
		for (const auto &result : results) {
			s << "<tr>";
			s << "<td>" << result.phrase << "</td>";
			s << "<td>" << result.value_singular << "</td>";
			s << "</tr>";
		}
		s << "</table>";
	}
}

void GematriaHTML::Begin(std::ostream &s) {
	s << "<!DOCTYPE html>";
	s << "<html>";
	s << "<body>";
	s << "<div>";
}

void GematriaHTML::Head(const GematriaCSS &css, std::ostream &s) {
	s << "<head>";
	// Generate the style
	{
		s << "<style>\n";
		for (const auto &[element, style] : css) {
			s << element << " {" << style << "}\n";
		}
		s << "</style>\n";
	}
	s << "</head>";
}

void GematriaHTML::End(std::ostream &stream) {
	stream << "</div>";
	stream << "</body>";
	stream << "</html>";
}
