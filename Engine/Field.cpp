#include "Field.h"
#include "SpriteEffect.h"
#include "Rect.h"
#include <fstream>

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

Field::Field(const std::string& filename)
	:
	background("Sprites\\background.bmp")
{
	std::ifstream map(filename);
	/*tiles.reserve(width * height);*/
	int i = 0;
	int rows = 0;
	for (std::string line; std::getline(map, line); )
	{
		for (auto c : line)
		{
			Wall wall;
			if (c == 'H')
			{
				wall = Wall::HardRock;
			}
			else if (c == 'R')
			{
				wall = Wall::Rock;
			}
			else if (c == 'S')
			{
				wall = Wall::Sand;
			}
			else
			{
				wall = Wall::None;
			}
			tiles.emplace_back(i % width, i / width, wall);
			i++;
		}
		rows++;
	}
	height = rows;
	width = tiles.size() / height;
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
