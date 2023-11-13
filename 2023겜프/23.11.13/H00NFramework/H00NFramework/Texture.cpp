#include "pch.h"
#include "Texture.h"
#include "Core.h"

Texture::Texture() : hBitmap{ 0 }, hDC{0}
{
}

Texture::~Texture()
{
	DeleteDC(hDC);
	DeleteObject(hBitmap);
}

void Texture::Load(const std::wstring& filePath)
{
	hBitmap = (HBITMAP)LoadImage(
		nullptr, 
		filePath.c_str(), 
		IMAGE_BITMAP, 
		0, 0, 
		LR_CREATEDIBSECTION | LR_LOADFROMFILE
	);

	assert(hBitmap);

	hDC = CreateCompatibleDC(Core::GetInstance()->GetMainHDC());
	SelectObject(hDC, hBitmap);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
}
