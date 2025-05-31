#include "Font.h"
#include "SpriteEffect.h"
#include <cassert>

Font::Font(const std::string& filename, Color chroma)
	:
	surf(filename),
	chroma(chroma),
	glyphWidth(surf.GetWidth() / nColumns),
	glyphHeight(surf.GetHeight() / nRows)
{
	assert(glyphWidth * nColumns == surf.GetWidth());
	assert(glyphHeight * nRows == surf.GetHeight());
}

void Font::Draw(const std::string& text, const Vec2I& pos, Color sub, Graphics& gfx) const
{
	SpriteEffect::Substitution effect{ chroma, sub };
	Vec2I curPos = pos;
	for (auto c : text)
	{
		if (c == '\n')
		{
			curPos.x = pos.x;
			curPos.y += glyphHeight;
		}
		else
		{
			if (c > firstGlyph && c <= lastGlyph)
			{
				gfx.DrawSprite(curPos.x, curPos.y, MapGlyphRect(c), surf, effect);
			}
			curPos.x += glyphWidth;
		}
	}
}

RectI Font::MapGlyphRect(char c) const
{
	const int n = c - firstGlyph;
	const int x = n % nColumns;
	const int y = n / nColumns;
	return RectI(x * glyphWidth, (x + 1) * glyphWidth, y * glyphHeight, (y + 1) * glyphHeight);
}
