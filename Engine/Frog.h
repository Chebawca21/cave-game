#pragma once
#include "Vec2.h"
#include "Surface.h"
#include "Animation.h"
#include <vector>

class Frog
{
private:
	enum class Position
	{
		Standing,
		Count
	};
public:
	Frog(int x, int y);
	void Update(const Vec2I& dir, float dt);
	void Draw(const Vec2I& screenPos, Graphics& gfx) const;
private:
	static constexpr int width = 32;
	static constexpr int height = 32;
	Vec2I pos;
	Surface sprite;
	std::vector<Animation> animations;
	int curAnim = 0;
};