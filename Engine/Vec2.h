#pragma once
#include <cmath>

template<typename T>
class Vec2
{
public:
	Vec2() = default;
	Vec2(T x, T y)
		:
		x(x),
		y(y)
	{}
	template<typename U>
	explicit Vec2(const Vec2<U>& src)
		:
		x(T(src.x)),
		y(T(src.y))
	{
	}
	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}
	Vec2 operator*(Vec2<T> rhs) const
	{
		return Vec2(x * rhs.x, y * rhs.y);
	}
	Vec2& operator*=(Vec2<T> rhs)
	{
		return *this = *this * rhs;
	}
	Vec2 operator*(T rhs) const
	{
		return Vec2(x * rhs, y * rhs);
	}
	Vec2& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}
	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}
	Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}
	Vec2 operator/(int rhs) const
	{
		return Vec2(x / rhs, y / rhs);
	}
	Vec2& operator/=(int rhs)
	{
		return *this = *this / rhs;
	}
	T GetLength() const
	{
		return T(std::sqrt(GetLengthSq()));
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	Vec2& Normalize()
	{
		return *this = GetNormalized();
	}
	Vec2 GetNormalized() const
	{
		const T len = GetLength();
		if (len != T(0))
		{
			return *this * (T(1) / len);
		}
		return *this;
	}
public:
	T x;
	T y;
};

using Vec2I = Vec2<int>;
using Vec2F = Vec2<float>;