#pragma once
#include "Graphics.h"

namespace SpriteEffect
{
	class Copy
	{
	public:
		void operator()(int x, int y, Color c, Graphics& gfx) const
		{
			gfx.PutPixel(x, y, c);
		}
	};
	class Chroma
	{
	public:
		Chroma(Color c)
			:
			chroma(c)
		{}
		void operator()(int x, int y, Color c, Graphics& gfx) const
		{
			if (chroma != c)
			{
				gfx.PutPixel(x, y, c);
			}
		}
	private:
		Color chroma;
	};
	class Substitution
	{
	public:
		Substitution(Color c, Color s)
			:
			chroma(c),
			substitute(s)
		{}
		void operator()(int x, int y, Color c, Graphics& gfx) const
		{
			if (chroma != c)
			{
				gfx.PutPixel(x, y, substitute);
			}
		}
	private:
		Color chroma;
		Color substitute;
	};
};