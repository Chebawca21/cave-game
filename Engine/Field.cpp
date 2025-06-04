#include "Field.h"
#include "SpriteEffect.h"
#include "Rect.h"

Field::Tile::Tile(int x, int y, Wall wall)
	:
	pos({x, y}),
	wall(wall)
{
}

void Field::Tile::SetWall(Field::Wall wall)
{
	this->wall = wall;
}

void Field::Tile::Draw(const Vec2I& screenPos, const Surface& sprite, Graphics& gfx) const
{
	const int x = screenPos.x + (pos.x * width);
	const int y = screenPos.y + (pos.y * height);
	auto effect = SpriteEffect::Copy();
	gfx.DrawSprite(x, y, {{width * int(wall), 0}, width, height}, sprite, effect);
}

Field::Wall Field::Tile::GetWall() const
{
	return wall;
}

Field::Field()
	:
	background("Sprites\\background.bmp")
{
	tiles.reserve(width * height);
	for (int i = 0; i < width * height; i++)
	{
		Wall wall;
		if (i % width == 0 || i % width == width - 1 || i < width || i > (width * height) - width)
		{
			wall = Wall::HardRock;
		}
		else if (i % 5 == 0)
		{
			wall = Wall::Rock;
		}
		else if (i % 4 == 0)
		{
			wall = Wall::Sand;
		}
		else
		{
			wall = Wall::None;
		}
		tiles.emplace_back( i % width, i / width, wall );
	}
}

Field::Wall Field::GetWall(Vec2I pos) const
{
	return tiles[pos.y * width + pos.x].GetWall();
}

void Field::Draw(Graphics& gfx) const
{
	for (int i = 0; i < width * height; i++)
	{
		tiles[i].Draw({ 0, 0 }, background, gfx);
	}
}

void Field::DestroyWall(const Vec2I& pos)
{
	tiles[pos.y * width + pos.x].SetWall(Field::Wall::None);
}
