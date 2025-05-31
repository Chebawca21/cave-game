#pragma once
#include "Surface.h"
#include "Vec2.h"
#include "Graphics.h"

class Font
{
public:
	Font(const std::string& filename, Color chroma = Colors::White);
	void Draw(const std::string& text, const Vec2I& pos, Color sub, Graphics& gfx) const;
private:
	RectI MapGlyphRect(char c) const;
private:
	Surface surf;
	Color chroma;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	static constexpr char firstGlyph = ' ';
	static constexpr char lastGlyph = '~';
};