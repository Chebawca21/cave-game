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
	static Type GetType(char c);
	static bool IsWalkable(Type type);
	static bool IsPushable(Type type);
	static bool IsFalling(Type type);
	static bool IsSlippery(Type type);
	static bool IsExplodable(Type type);
	static void Draw(const Vec2I& pos, Type type, const Surface& sprite, Color chroma, Graphics& gfx);
private:
	static constexpr int width = 32;
	static constexpr int height = 32;
};