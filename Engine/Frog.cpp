#include "Frog.h"

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
	if (dir.x > 0)
	{
		pos.x++;
	}
	else if (dir.x < 0)
	{
		pos.x--;
	}
	else if (dir.y > 0)
	{
		pos.y++;
	}
	else if (dir.y < 0)
	{
		pos.y--;
	}
	animations[curAnim].Update(dt);
}

void Frog::Draw(const Vec2I& screenPos, Graphics& gfx) const
{
	animations[curAnim].Draw(screenPos + (pos * Vec2I(width, height)), gfx);
}
