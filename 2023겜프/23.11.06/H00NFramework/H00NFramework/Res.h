#pragma once

class Res
{
public:
	Res();
	~Res();

public:
	void SetKey(const std::wstring& key) { this->key = key; }
	void SetRelativePath(const std::wstring& relativePath) { this->relativePath = relativePath; }

public:
	const std::wstring& GetKey() const { return key; }
	const std::wstring& GetRelativePath() const { return relativePath; }

private:
	std::wstring key;
	std::wstring relativePath;
};
