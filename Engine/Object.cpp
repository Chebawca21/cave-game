#include "Object.h"
#include "SpriteEffect.h"

Object::Type Object::GetType(char c)
{
	if (c == 'H')
	{
		return Object::Type::HardRock;
	}
	else if (c == 'R')
	{
		return Object::Type::Rock;
	}
	else if (c == 'S')
	{
		return Object::Type::Sand;
	}
	else if (c == 'B')
	{
		return Object::Type::Boulder;
	}
	else if (c == 'F')
	{
		return Object::Type::Frog;
	}
	else
	{
		return Object::Type::None;
	}
}

bool Object::IsWalkable(Type type)
{
	switch (type)
	{
	case Object::Type::None:
		return true;
	case Object::Type::Sand:
		return true;
	case Object::Type::Rock:
		return false;
	case Object::Type::HardRock:
		return false;
	case Object::Type::Boulder:
		return false;
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return true;
	case Object::Type::Frozen:
		return false;
	default:
		return true;
	}
}

bool Object::IsPushable(Type type)
{
	switch (type)
	{
	case Object::Type::None:
		return false;
	case Object::Type::Sand:
		return false;
	case Object::Type::Rock:
		return false;
	case Object::Type::HardRock:
		return false;
	case Object::Type::Boulder:
		return true;
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return false;
	case Object::Type::Frozen:
		return false;
	default:
		return true;
	}
}

bool Object::IsFalling(Type type)
{
	switch (type)
	{
	case Object::Type::None:
		return false;
	case Object::Type::Sand:
		return false;
	case Object::Type::Rock:
		return false;
	case Object::Type::HardRock:
		return false;
	case Object::Type::Boulder:
		return true;
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return false;
	case Object::Type::Frozen:
		return false;
	default:
		return false;
	}
}

bool Object::IsSlippery(Type type)
{
	switch (type)
	{
	case Object::Type::None:
		return false;
	case Object::Type::Sand:
		return true;
	case Object::Type::Rock:
		return false;
	case Object::Type::HardRock:
		return false;
	case Object::Type::Boulder:
		return true;
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return false;
	case Object::Type::Frozen:
		return false;
	default:
		return false;
	}
}

bool Object::IsExplodable(Type type)
{
	switch (type)
	{
	case Object::Type::None:
		return true;
	case Object::Type::Sand:
		return true;
	case Object::Type::Rock:
		return true;
	case Object::Type::HardRock:
		return false;
	case Object::Type::Boulder:
		return true;
	case Object::Type::Mine:
		return true;
	case Object::Type::Explosion:
		return true;
	case Object::Type::Frog:
		return true;
	case Object::Type::Frozen:
		return false;
	default:
		return true;
	}
}

void Object::Draw(const Vec2I& pos, Type type, const Surface& sprite, Color chroma, Graphics& gfx)
{
	switch (type)
	{
	case Object::Type::Sand:
		gfx.DrawSprite(pos.x, pos.y, { {width * 1, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
		break;
	case Object::Type::Rock:
		gfx.DrawSprite(pos.x, pos.y, { {width * 2, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
		break;
	case Object::Type::HardRock:
		gfx.DrawSprite(pos.x, pos.y, { {width * 3, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
		break;
	case Object::Type::Boulder:
		gfx.DrawSprite(pos.x, pos.y, { {width * 4, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
		break;
	case Object::Type::Mine:
		gfx.DrawSprite(pos.x, pos.y, { {width * 5, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
		break;
	case Object::Type::Explosion:
		gfx.DrawSprite(pos.x, pos.y, { {width * 6, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
		break;
	default:
		break;
	}
}
