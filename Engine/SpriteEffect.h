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
	class Blend
	{
	public:
		Blend(Color c, Color b, float p)
			:
			chroma(c),
			blend(b),
			percentage(p)
		{}
		void operator()(int x, int y, Color c, Graphics& gfx) const
		{
			if (chroma != c)
			{
				unsigned char r = c.GetR() - unsigned char(float((c.GetR() - blend.GetR()) * percentage));
				unsigned char g = c.GetG() - unsigned char(float((c.GetG() - blend.GetG()) * percentage));
				unsigned char b = c.GetB() - unsigned char(float((c.GetB() - blend.GetB()) * percentage));
				gfx.PutPixel(x, y, { r, g , b });
			}
		}
	private:
		Color chroma;
		Color blend;
		float percentage;
	};
};