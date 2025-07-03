#include "Object.h"
#include "SpriteEffect.h"
#include <cmath>

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
	return walkable;
}

bool Object::IsPushable() const
{
	return pushable;
}

bool Object::IsFallable() const
{
	return fallable;
}

bool Object::IsSlippery() const
{
	return slippery;
}

bool Object::IsExplodable() const
{
	return explodable;
}

bool Object::Update(float dt)
{
	return false;
}

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
	// true indicates that the timer reached zero and tile can be unfrozen
	curr_freeze_time -= dt;
	if (curr_freeze_time <= 0.0f)
	{
		return true;
	}
	return false;
}

Mine::Mine()
	:
	Object(false, false, false, false, true)
{
}
void Mine::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
	float percentage = curr_time / blend_cycle;
	if (int(std::floor(percentage)) % 2 == 0)
	{
		percentage = 1 - std::fmod(percentage, 1.0f);
	}
	else
	{
		percentage = std::fmod(percentage, 1.0f);
	}
	auto effect = SpriteEffect::Blend(chroma, blend, percentage);
	gfx.DrawSprite(pos.x, pos.y, { {width * 5, 0}, width, height }, sprite, effect);
}

Object::Type Mine::GetType() const
{
	return Type::Mine;
}

Object* Mine::clone() const
{
	return new Mine();
}

bool Mine::Update(float dt)
{
	// true indicates that the mine is set to explode
	curr_time += dt;
	if (curr_time >= explosion_time)
	{
		return true;
	}
	return false;
}

Explosion::Explosion()
	:
	Object(true, false, false, false, true)
{
}

void Explosion::Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, { {width * 6, 0}, width, height }, sprite, SpriteEffect::Chroma(chroma));
}

Object::Type Explosion::GetType() const
{
	return Type::Explosion;
}

Object* Explosion::clone() const
{
	return new Explosion();
}

bool Explosion::Update(float dt)
{
	// true indicates that the explosion should disappear
	curr_time += dt;
	if (curr_time >= explosion_time)
	{
		return true;
	}
	return false;
}
