#pragma once

#include "Vec2.h"

template<typename T>
class Rect
{
public:
	Rect() = default;
	Rect(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{}
	Rect(const Vec2<T>& topLeft, const Vec2<T>& bottomRight)
		:
		Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{}
	Rect(const Vec2<T>& topLeft, T width, T height)
		:
		Rect(topLeft, topLeft + Vec2<T>(width, height))
	{}
	bool IsOverlappingWith(const Rect& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}
	bool IsContainedBy(const Rect& other) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}
	bool Contains(const Vec2<T>& point) const
	{
		return point.x >= left && point.x < right && point.y >= top && point.y < bottom;
	}
	Rect FromCenter(const Vec2<T>& center, T halfWidth, T halfHeight)
	{
		const Vec2<T> half(halfWidth, halfHeight);
		return Rect(center - half, center + half);
	}
	Rect GetExpanded(T offset) const
	{
		return Rect(left - offset, right + offset, top - offset, bottom + offset);
	}
	Vec2<T> GetCenter() const
	{
		return Vec2<T>((left + right) / 2, (top + bottom) / 2);
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};

using RectI = Rect<int>;
using RectF = Rect<float>;