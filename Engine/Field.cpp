#include "Field.h"
#include "SpriteEffect.h"
#include "Rect.h"
#include <fstream>

Field::Tile::Tile(int x, int y, Object::Type type)
	:
	pos({x, y}),
	type(type)
{
}

void Field::Tile::SetObject(Object::Type type)
{
	this->type = type;
}

void Field::Tile::Update(float dt, Field& field)
{
	if (vel.GetLength() != 0)
	{
		dist += vel * dt;
		if (abs(dist.x) >= abs(width) || abs(dist.y) >= abs(height))
		{
			dist = { 0.0f, 0.0f };
			vel = { 0.0f, 0.0f };
			if (falling)
			{
				falling = false;
			}
		}
	}
	if (Object::IsFalling(type) && vel.GetLength() == 0)
	{
		if (field.PushObject(pos, { 0, 1 }))
		{
			field.StartFalling(pos + Vec2I(0, 1));
		}
	}
	if (type == Object::Type::Frozen)
	{
		curr_freeze_time -= dt;
		if (curr_freeze_time <= 0.0f)
		{
			curr_freeze_time = 0.0f;
			type = Object::Type::None;
		}
	}
}

void Field::Tile::Draw(const Vec2I& screenPos, const Surface& sprite, Graphics& gfx) const
{
	Vec2I posFixed = pos;
	if (vel.GetLength() > 0.0f)
	{
		posFixed -= Vec2I(vel.GetNormalized());
	}
	const int x = screenPos.x + (posFixed.x * width) + int(dist.x);
	const int y = screenPos.y + (posFixed.y * height) + int(dist.y);
	auto effect = SpriteEffect::Copy();
	Object::Draw({ x, y }, type, sprite, chroma, gfx);
}

bool Field::Tile::IsEmpty() const
{
	return type == Object::Type::None;
}

void Field::Tile::SetMotion(const Vec2I& dir)
{
	vel += Vec2F(dir) * speed;
}

void Field::Tile::Freeze()
{
	type = Object::Type::Frozen;
	curr_freeze_time = freeze_time;
}

bool Field::Tile::IsFalling() const
{
	return falling;
}

void Field::Tile::StartFalling()
{
	falling = true;
}

Object::Type Field::Tile::GetObjectType() const
{
	return type;
}

Vec2I Field::Tile::GetPos() const
{
	return pos;
}

Field::Field(const std::string& filename)
	:
	sprite_objects("Sprites\\objects.bmp")
{
	std::ifstream map(filename);
	/*tiles.reserve(width * height);*/
	int i = 0;
	int rows = 0;
	for (std::string line; std::getline(map, line); )
	{
		for (auto c : line)
		{
			tiles.emplace_back(i % width, i / width, Object::GetType(c));
			i++;
		}
		rows++;
	}
	height = rows;
	width = int(tiles.size()) / height;
}

void Field::Update(float dt)
{
	for (auto& t : tiles)
	{
		t.Update(dt, *this);
	}
}

Object::Type Field::GetObjectType(Vec2I pos) const
{
	return tiles[pos.y * width + pos.x].GetObjectType();
}

Vec2I Field::GetFrogPos() const
{
	for (auto t : tiles)
	{
		if (t.GetObjectType() == Object::Type::Frog)
		{
			return t.GetPos();
		}
	}
	return { -1, -1 };
}

bool Field::PushObject(const Vec2I& pos, const Vec2I& dir)
{
	const auto movedPos = pos + dir;
	auto currTile = &tiles[pos.y * width + pos.x];
	auto nextTile = &tiles[movedPos.y * width + movedPos.x];
	if (nextTile->IsEmpty())
	{
		nextTile->SetObject(currTile->GetObjectType());
		nextTile->SetMotion(dir);
		currTile->Freeze();
		return true;
	}
	else
	{
		return false;
	}
}

void Field::MoveObject(const Vec2I& pos, const Vec2I& dir)
{
	const auto movedPos = pos + dir;
	auto currTile = &tiles[pos.y * width + pos.x];
	auto nextTile = &tiles[movedPos.y * width + movedPos.x];
	nextTile->SetObject(currTile->GetObjectType());
	nextTile->SetMotion(dir);
	currTile->SetObject(Object::Type::None);
}

bool Field::IsFalling(const Vec2I& pos) const
{
	return tiles[pos.y * width + pos.x].IsFalling();
}

void Field::StartFalling(const Vec2I& pos)
{
	tiles[pos.y * width + pos.x].StartFalling();
}

void Field::Draw(Graphics& gfx) const
{
	for (int i = 0; i < width * height; i++)
	{
		tiles[i].Draw({ 0, 0 }, sprite_objects, gfx);
	}
}

void Field::DestroyObject(const Vec2I& pos)
{
	tiles[pos.y * width + pos.x].SetObject(Object::Type::None);
}
