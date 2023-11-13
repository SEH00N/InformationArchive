#pragma once

class Texture;

class ResManager
{
	SINGLE(ResManager)

private:
	std::map<std::wstring, Texture*> texMap;

public:
	Texture* TexLoad(const std::wstring& key, const std::wstring& relativePath);
	Texture* TexFind(const std::wstring& key);
	void Release();
};

