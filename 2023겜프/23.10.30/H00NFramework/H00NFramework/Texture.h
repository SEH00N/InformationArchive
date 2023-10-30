#pragma once
#include "Res.h"

class Texture : public Res
{
public:
	Texture();
	~Texture();

public:
	void Load(const std::wstring& filePath);

public:
	const int& GetWidth() const { return bitmapInfo.bmWidth; }
	const int& GetHeight() const { return bitmapInfo.bmHeight; }
	const HDC& GetDC() const { return hDC; }

private:
	HBITMAP hBitmap;
	BITMAP bitmapInfo;
	HDC hDC;
};

