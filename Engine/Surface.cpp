#include "Surface.h"
#include "ChiliWin.h"
#include <fstream>
#include <cassert>

Surface::Surface(const std::string& filename)
{
	std::ifstream img(filename, std::ios::binary);
	assert(img);

	BITMAPFILEHEADER bmpFileHeader;
	img.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(bmpFileHeader));

	BITMAPINFOHEADER bmpInfoHeader;
	img.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
	assert(bmpInfoHeader.biBitCount == 24 || bmpInfoHeader.biBitCount == 32);
	assert(bmpInfoHeader.biCompression == BI_RGB);

	width = bmpInfoHeader.biWidth;
	if (bmpInfoHeader.biHeight < 0)
	{
		height = -bmpInfoHeader.biHeight;
	}
	else
	{
		height = bmpInfoHeader.biHeight;
	}
	pPixels = new Color[width * height];

	img.seekg(bmpFileHeader.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;
	for (int i = 0; i < height; i++)
	{
		int y;
		if (bmpInfoHeader.biHeight > 0)
		{
			y = height - 1 - i;
		}
		else
		{
			y = i;
		}
		for (int x = 0; x < width; x++)
		{
			if (bmpInfoHeader.biBitCount == 24)
			{
				SetPixel(x, y, Color(img.get(), img.get(), img.get()));
			}
			if (bmpInfoHeader.biBitCount == 32)
			{
				SetPixel(x, y, Color(img.get(), img.get(), img.get(), img.get()));
			}
		}
		if (bmpInfoHeader.biBitCount == 24)
		{
			img.seekg(padding, std::ios::cur);
		}
	}
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels(new Color[width * height])
{
}

Surface::~Surface()
{
	delete pPixels;
	pPixels = nullptr;
}

Surface::Surface(const Surface& rhs)
	:
	Surface(rhs.width, rhs.height)
{
	for (int i = 0; i < width * height; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface Surface::operator=(const Surface& rhs)
{
	width = rhs.width;
	height = rhs.height;

	delete[] pPixels;
	pPixels = new Color[width * height];
	for (int i = 0; i < width * height; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
	return *this;
}

void Surface::SetPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
