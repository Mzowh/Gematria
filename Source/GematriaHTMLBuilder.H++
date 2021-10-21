// HTML module
#pragma once
#include "Gematria.H++"
#include <unordered_map>
#include <sstream>

namespace GematriaHTML
{
	// Map of names to style
	using CSSElementName = std::string;
	using CSSElementStyle = std::string;
	using GematriaCSS = std::unordered_map<CSSElementName, CSSElementStyle>;

	void OutputGematriaHTML(const Gematria &gematria, const GematriaCSS &css, std::stringstream &stream);
}