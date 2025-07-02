#include "Object.h"
#include "SpriteEffect.h"

Object::Object(bool walkable, bool pushable, bool fallable, bool slippery, bool explodable)
	:
	walkable(walkable),
	pushable(pushable),
	fallable(fallable),
	slippery(slippery),
	explodable(explodable)
{}

bool Object::IsWalkable() const
{
	/*switch (type)
	{
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return true;
	default:
		return true;
	}*/
	return walkable;
}

bool Object::IsPushable() const
{
	/*switch (type)
	{
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return false;
	default:
		return true;
	}*/
	return pushable;
}

bool Object::IsFallable() const
{
	/*switch (type)
	{
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return false;
	default:
		return false;
	}*/
	return fallable;
}

bool Object::IsSlippery() const
{
	/*switch (type)
	{
	case Object::Type::Mine:
		return false;
	case Object::Type::Explosion:
		return false;
	default:
		return false;
	}*/
	return slippery;
}

bool Object::IsExplodable() const
{
	/*switch (type)
	{
	case Object::Type::Mine:
		return true;
	case Object::Type::Explosion:
		return true;
	case Object::Type::Frog:
		return true;
	default:
		return true;
	}*/
	return explodable;
}

bool Object::Update(float dt)
{
	return false;
}


//void Object::Draw(const Vec2I& pos, Type type, const Surface& sprite, Color chroma, Graphics& gfx)
//{
//	switch (type)
//	{
//	case Object::Type::Mine:
//		gfx.DrawSprite(pos.x, pos.y, { {width * 5, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
//		break;
//	case Object::Type::Explosion:
//		gfx.DrawSprite(pos.x, pos.y, { {width * 6, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
//		break;
//	default:
//		break;
//	}
//}

None::None()
	:
	Object(true, false, false, false, true)
{
}

void None::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
}

Object::Type None::GetType() const
{
	return Type::None;
}

Object* None::clone() const
{
	return new None();
}

HardRock::HardRock()
	:
	Object(false, false, false, false, false)
{
}

void HardRock::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, { {width * 3, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
}

Object::~Object()
{
}

Object::Type HardRock::GetType() const
{
	return Type::HardRock;
}

Object* HardRock::clone() const
{
	return new HardRock();
}

Rock::Rock()
	:
	Object(false, false, false, false, true)
{
}

void Rock::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, { {width * 2, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
}

Object::Type Rock::GetType() const
{
	return Type::Rock;
}

Object* Rock::clone() const
{
	return new Rock();
}

Sand::Sand()
	:
	Object(true, false, false, true, true)
{
}

void Sand::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, { {width * 1, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
}

Object::Type Sand::GetType() const
{
	return Type::Sand;
}

Object* Sand::clone() const
{
	return new Sand();
}

Boulder::Boulder()
	:
	Object(false, true, true, true, true)
{
}

void Boulder::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, { {width * 4, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
}

Object::Type Boulder::GetType() const
{
	return Type::Frozen;
}

Object* Boulder::clone() const
{
	return new Boulder();
}

Frozen::Frozen()
	:
	Object(false, false, false, false, false),
	curr_freeze_time(freeze_time)
{
}

void Frozen::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
}

Object::Type Frozen::GetType() const
{
	return Type::Frozen;
}

Object* Frozen::clone() const
{
	return new Frozen();
}

bool Frozen::Update(float dt)
{
	curr_freeze_time -= dt;
	if (curr_freeze_time <= 0.0f)
	{
		return true;
	}
	return false;
}
