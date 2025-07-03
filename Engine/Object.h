#pragma once
#include "Surface.h"
#include "Graphics.h"

class Object
{
public:
	enum class Type
	{
		None,
		Sand,
		Rock,
		HardRock, 
		Boulder,
		Mine,
		Explosion,
		Frog,
		Frozen
	};
public:
	Object(bool walkable, bool pushable, bool fallable, bool slippery, bool explodable);
	bool IsWalkable() const;
	bool IsPushable() const;
	bool IsFallable() const;
	bool IsSlippery() const;
	bool IsExplodable() const;
	virtual Type GetType() const = 0;
	virtual bool Update(float dt);
	virtual void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const = 0;
	virtual Object* clone() const = 0;
	virtual ~Object();
protected:
	static constexpr int width = 32;
	static constexpr int height = 32;
	const bool walkable;
	const bool pushable;
	const bool fallable;
	const bool slippery;
	const bool explodable;
};

class None : public Object
{
public:
	None();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
};

class HardRock : public Object
{
public:
	HardRock();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
};

class Rock : public Object
{
public:
	Rock();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
};

class Sand : public Object
{
public:
	Sand();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
};

class Boulder : public Object
{
public:
	Boulder();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
};

class Frozen : public Object
{
public:
	Frozen();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
	bool Update(float dt) override;
private:
	static constexpr float freeze_time = 0.5f;
	float curr_freeze_time = 0.0f;
};

class Mine : public Object
{
public:
	Mine();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
	bool Update(float dt) override;
private:
	static constexpr float explosion_time = 4.0f;
	static constexpr Color blend = Colors::White;
	static constexpr float blend_cycle = explosion_time / 4;
	float curr_time = 0.0f;
};

class Explosion : public Object
{
public:
	Explosion();
	void Draw(const Vec2I& pos, const Surface& sprite, Color chroma, Graphics& gfx) const override;
	Type GetType() const override;
	Object* clone() const override;
	bool Update(float dt) override;
private:
	static constexpr float explosion_time = 2.0f;
	float curr_time = 0.0f;
};