#pragma once
#include "Vec2.h"

class Boulder
{
public:
	Boulder(int x, int y);
private:
	static constexpr int width = 32;
	static constexpr int height = 32;
	static constexpr float speed = 64.0f;
	Vec2I pos;
	Vec2F dist = { 0.0f, 0.0f };
	Vec2F vel = { 0.0f, 0.0f };
};