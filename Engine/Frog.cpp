#include "Frog.h"
#include <cmath>

Frog::Frog(int x, int y)
	:
	pos({x, y}),
	sprite("Sprites\\frog.bmp")
{
	animations.reserve(int(Position::Count));
	for (int i = 0; i < int(Position::Count); i++)
	{
		animations.emplace_back(0, 0, width, height, 1, sprite);
	}
}

void Frog::Update(const Vec2I& dir, float dt)
{
	if (vel.GetLength() == 0.0f)
	{
		pos += dir;
		vel += Vec2F(dir) * speed;
		dist += vel * dt;
	}
	else
	{
		dist += vel * dt;
		if (abs(dist.x) >= abs(width) || abs(dist.y) >= abs(height))
		{
			dist = { 0.0f, 0.0f };
			vel = { 0.0f, 0.0f };
		}
	}
	animations[curAnim].Update(dt);
}

void Frog::Draw(const Vec2I& screenPos, Graphics& gfx) const
{
	Vec2I posFixed = pos;
	if (vel.GetLength() > 0.0f)
	{
		posFixed -= Vec2I(vel.GetNormalized());
	}
	animations[curAnim].Draw((screenPos + Vec2I(dist)) + (posFixed * Vec2I(width, height)), gfx);
}
