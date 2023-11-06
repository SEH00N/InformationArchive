#pragma once
class PathManager
{
	SINGLE(PathManager)

public:
	void Init();

	const wchar_t* GetResourcePath() const {
		return resourcePath;
	}

private:
	wchar_t resourcePath[255];
};

