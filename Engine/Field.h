#pragma once
#include "Object.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Object.h"
#include <vector>

class Field
{
private:
	class Tile
	{
	public:
		Tile(int x, int y, Object* pObj);
		Tile(const Tile& src);
		Tile& operator=(const Tile&) = delete;
		void SetObject(Object* p);
		void SetObjectPointer(Object* p); // Same as set object but without deleting pObj
		void Update(float dt, Field& field);
		void Draw(const Vec2I& screenPos, const Surface& sprite, Graphics& gfx) const;
		bool IsEmpty() const;
		void SetMotion(const Vec2I& dir);
		void Freeze();
		bool IsFalling() const;
		void StartFalling();
		Object* GetObjectPointer() const;
		Vec2I GetPos() const;
		~Tile();
	private:
		void Unfreeze();
	private:
		static constexpr int width = 32;
		static constexpr int height = 32;
		static constexpr float speed = 80.0f;
		Vec2I pos;
		Object* pObj;
		Vec2F dist = { 0.0f, 0.0f };
		Vec2F vel = { 0.0f, 0.0f };
		bool falling = false;
	};
public:
	Field(const std::string& filename);
	void SetFrogPos(const Vec2I& pos);
	void Update(float dt);
	void Draw(Graphics& gfx) const;
	void DestroyObject(const Vec2I& pos);
	Object* GetObjectPointer(Vec2I pos) const;
	Vec2I GetFrogPos() const;
	bool PushObject(const Vec2I& pos, const Vec2I& dir);
	void MoveObject(const Vec2I& pos, const Vec2I& dir);
	bool IsEmpty(const Vec2I& pos) const;
	bool IsFalling(const Vec2I& pos) const;
	void Freeze(const Vec2I& pos);
	void SpawnMine();
private:
	void StartFalling(const Vec2I& pos);
	void Explode(const Vec2I& pos);
private:
	static constexpr Color chroma = Colors::Magenta;
	Surface sprite_objects;
	std::vector<Tile> tiles;
	Vec2I frogPos;
	int width = 18;
	int height = 10;
};