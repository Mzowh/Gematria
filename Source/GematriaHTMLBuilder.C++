#include "GematriaHTMLBuilder.H++"

// Generates HTML for a Single Gematria instance
void GematriaHTML::OutputGematriaHTML(const Gematria &gematria, const GematriaCSS &css, std::stringstream &stream) {
	stream << "<!DOCTYPE html>";
	stream << "<html>";
	// Generate the Head
	{
		stream << "<head>";
		// Generate the style
		{
			stream << "<style>\n";
			for (const auto &[element, style] : css) {
				stream << element << " {" << style << "}\n";
			}
			stream << "</style>\n";
		}
		stream << "</head>";
	}

	// Generate the Body
	{
		stream << "<body>";
		stream << "<div>";
		// Generate Phrase Table
		{
			for (const auto &[value, phrases] : gematria.GetPhraseResultsMap()) {
				stream << "<table>";
				stream << "<h2>Value " << value << "</h2>";
				stream << "<h4>Size: " << phrases.size() << "</h4>";
				stream << "<tr><th>Phrase</th><th>Special</th></tr>";
				std::size_t index = 0;
				for (const auto &data : phrases) {
					stream << "<tr>\n";
					stream << "<td>" << data.original << "</td>";
					stream << "<td>";
					{ // Generate Specials Table
						if (!data.special.comment.empty()) stream << data.special.comment;
					}
					stream << "</td>";
					stream << "</tr>";
					++index;
				}
				stream << "</table>\n";
				stream << "<br>\n";
			}
		}
		stream << "</div>";
		stream << "</body>";
	}
	stream << "</html>";
}