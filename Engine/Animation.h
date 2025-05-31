#pragma once
#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation(int x, int y, int width, int height, int nFrames, const Surface& sprite, Color chroma = Colors::Magenta);
	void Draw(const Vec2I& pos, Graphics& gfx) const;
	void Draw(const Vec2I& pos, const RectI& clip, Graphics& gfx) const;
	void Update(float dt);
private:
	void Advance();
private:
	Color chroma;
	const Surface& sprite;
	std::vector<RectI> frames;
	int curFrame = 0;
	float holdTime = 0.16f;
	float curFramTime = 0.0f;
};