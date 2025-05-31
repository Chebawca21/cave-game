#pragma once
#include "Colors.h"
#include <string>

class Surface
{
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	~Surface();
	Surface(const Surface& rhs);
	Surface operator=(const Surface& rhs);
	void SetPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	int width;
	int height;
	Color* pPixels = nullptr;
};