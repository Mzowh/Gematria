// HTML module
#pragma once
#include "Gematria.H++"
#include <unordered_map>
#include <ostream>

namespace GematriaHTML
{
	// Map of names to style
	using CSSElementName = std::string;
	using CSSElementStyle = std::string;
	using GematriaCSS = std::unordered_map<CSSElementName, CSSElementStyle>;


	void Begin(std::ostream &stream);
	void Head(const GematriaCSS& css, std::ostream &stream);
	void MultiMapBody(const GematriaMultimap &gematria, std::ostream &stream);
	void SingularBody(const GematriaSingular &gematria, std::ostream &stream);
	void End(std::ostream& stream);
}