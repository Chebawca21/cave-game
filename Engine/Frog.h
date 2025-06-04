#pragma once
#include "Vec2.h"
#include "Surface.h"
#include "Animation.h"
#include "Field.h"
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
	void Update(const Vec2I& dir, float dt, Field& field);
	void Draw(const Vec2I& screenPos, Graphics& gfx) const;
	Vec2I GetPos() const;
private:
	static constexpr int width = 32;
	static constexpr int height = 32;
	static constexpr float speed = 64.0f;
	Vec2I pos;
	Vec2F dist = { 0.0f, 0.0f };
	Vec2F vel = { 0.0f, 0.0f };
	Surface sprite;
	std::vector<Animation> animations;
	int curAnim = 0;
};