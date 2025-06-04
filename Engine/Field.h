#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include <vector>

class Field
{
private:
	class Tile
	{
	public:
		enum class Wall
		{
			None,
			Sand,
			Rock,
			HardRock
		};
	public:
		Tile(int x, int y, Wall wall);
		void SetPos(const Vec2I& pos);
		void Draw(const Vec2I& screenPos, const Surface& sprite, Graphics& gfx) const;
	private:
		static constexpr int width = 32;
		static constexpr int height = 32;
		Vec2I pos;
		Wall wall = Wall::None;
	};
public:
	Field();
	void Draw(Graphics& gfx) const;
private:
	Surface background;
	std::vector<Tile> tiles;
	const int width = 18;
	const int height = 10;
};