#pragma once
#include "Object.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Boulder.h"
#include <vector>

class Field
{
private:
	class Tile
	{
	public:
		Tile(int x, int y, Object::Type type);
		void SetObject(Object::Type type);
		void Update(float dt, Field& field);
		void Draw(const Vec2I& screenPos, const Surface& sprite, Graphics& gfx) const;
		bool IsEmpty() const;
		void SetMotion(const Vec2I& dir);
		void Freeze();
		bool IsFalling() const;
		void StartFalling();
		Object::Type GetObjectType() const;
		Vec2I GetPos() const;
	private:
		static constexpr int width = 32;
		static constexpr int height = 32;
		static constexpr float speed = 64.0f;
		static constexpr float freeze_time = 0.5f;
		Vec2I pos;
		Object::Type type;
		Vec2F dist = { 0.0f, 0.0f };
		Vec2F vel = { 0.0f, 0.0f };
		float curr_freeze_time = 0.0f;
		bool falling = false;
	};
public:
	Field(const std::string& filename);
	void Update(float dt);
	void Draw(Graphics& gfx) const;
	void DestroyObject(const Vec2I& pos);
	Object::Type GetObjectType(Vec2I pos) const;
	Vec2I GetFrogPos() const;
	bool PushObject(const Vec2I& pos, const Vec2I& dir);
	void MoveObject(const Vec2I& pos, const Vec2I& dir);
	bool IsFalling(const Vec2I& pos) const;
private:
	void StartFalling(const Vec2I& pos);
private:
	static constexpr Color chroma = Colors::Magenta;
	Surface sprite_objects;
	std::vector<Tile> tiles;
	int width = 18;
	int height = 10;
};