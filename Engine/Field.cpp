#include "Field.h"
#include "SpriteEffect.h"
#include "Rect.h"
#include <fstream>

Field::Tile::Tile(int x, int y, Object* pObj)
	:
	pos({x, y}),
	pObj(pObj)
{
}

Field::Tile::Tile(const Tile& src)
	:
	pos(src.pos),
	pObj(src.pObj->clone())
{
}

void Field::Tile::SetObject(Object* p)
{
	delete pObj;
	pObj = p;
}

void Field::Tile::SetObjectPointer(Object* p)
{
	pObj = p;
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
	if (pObj->IsFallable() && vel.GetLength() == 0)
	{
		if (field.PushObject(pos, { 0, 1 }))
		{
			field.StartFalling(pos + Vec2I(0, 1));
		}
		else if (field.IsEmpty(pos + Vec2I(1, 0)) &&
				 field.GetObjectPointer(pos + Vec2I(0, 1))->IsSlippery() &&
				 field.IsEmpty(pos + Vec2I(1, 1)))
		{
			field.PushObject(pos, { 1, 0 });
			field.StartFalling(pos + Vec2I(1, 1));
		}
		else if (field.IsEmpty(pos + Vec2I(-1, 0)) && 
			     field.GetObjectPointer(pos + Vec2I(0, 1))->IsSlippery() &&
				 field.IsEmpty(pos + Vec2I(-1, 1)))
		{
			field.PushObject(pos, { -1, 0 });
			field.StartFalling(pos + Vec2I(-1, 1));
		}
	}
	if (pObj->GetType() == Object::Type::Frozen)
	{
		if (pObj->Update(dt))
		{
			Unfreeze();
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
	pObj->Draw({ x, y }, sprite, chroma, gfx);
}

bool Field::Tile::IsEmpty() const
{
	return pObj->GetType() == Object::Type::None;
}

void Field::Tile::SetMotion(const Vec2I& dir)
{
	vel += Vec2F(dir) * speed;
}

void Field::Tile::Freeze()
{
	// pObj is not deleted because freezing occurs after pObj is shallow copied
	pObj = new Frozen();
}

bool Field::Tile::IsFalling() const
{
	return falling;
}

void Field::Tile::StartFalling()
{
	falling = true;
}

Object* Field::Tile::GetObjectPointer() const
{
	return pObj;
}

Vec2I Field::Tile::GetPos() const
{
	return pos;
}

Field::Tile::~Tile()
{
	delete pObj;
	pObj = nullptr;
}

void Field::Tile::Unfreeze()
{
	delete pObj;
	pObj = new None();
}

Field::Field(const std::string& filename)
	:
	sprite_objects("Sprites\\objects.bmp"),
	frogPos({0, 0})
{
	std::ifstream map(filename);
	int i = 0;
	int rows = 0;
	for (std::string line; std::getline(map, line); )
	{
		for (auto c : line)
		{
			Object* pObj;
			if (c == 'H')
			{
				pObj = new HardRock();
			}
			else if (c == 'R')
			{
				pObj = new Rock();
			}
			else if (c == 'S')
			{
				pObj = new Sand();
			}
			else if (c == 'B')
			{
				pObj = new Boulder();
			}
			else if (c == 'F')
			{
				frogPos = { i % width, i / width };
				pObj = new None();
			}
			else
			{
				pObj = new None();
			}
			tiles.emplace_back(i % width, i / width, pObj);
			i++;
		}
		rows++;
	}
	height = rows;
	width = int(tiles.size()) / height;
}

void Field::SetFrogPos(const Vec2I& pos)
{
	frogPos = pos;
}

void Field::Update(float dt)
{
	for (auto& t : tiles)
	{
		t.Update(dt, *this);
	}
}

Object* Field::GetObjectPointer(Vec2I pos) const
{
	return tiles[pos.y * width + pos.x].GetObjectPointer();
}

Vec2I Field::GetFrogPos() const
{
	return frogPos;
}

bool Field::PushObject(const Vec2I& pos, const Vec2I& dir)
{
	const auto movedPos = pos + dir;
	auto currTile = &tiles[pos.y * width + pos.x];
	auto nextTile = &tiles[movedPos.y * width + movedPos.x];
	if (nextTile->IsEmpty() && movedPos != frogPos)
	{
		nextTile->SetObject(currTile->GetObjectPointer());
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
	nextTile->SetObject(currTile->GetObjectPointer());
	nextTile->SetMotion(dir);
	currTile->SetObjectPointer(new None());
}

bool Field::IsEmpty(const Vec2I& pos) const
{
	if (tiles[pos.y * width + pos.x].IsEmpty() &&
		pos != frogPos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Field::IsFalling(const Vec2I& pos) const
{
	return tiles[pos.y * width + pos.x].IsFalling();
}

void Field::Freeze(const Vec2I& pos)
{
	tiles[pos.y * width + pos.x].SetObject(new Frozen());
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
	tiles[pos.y * width + pos.x].SetObject(new None());
}
