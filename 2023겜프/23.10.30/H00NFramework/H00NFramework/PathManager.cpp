#include "pch.h"
#include "PathManager.h"
#include "Core.h"

void PathManager::Init()
{
	GetCurrentDirectory(255, resourcePath);
	wcscat_s(resourcePath, 255, L"\\Res\\");
	SetWindowText(Core::GetInstance()->GetHWnd(), resourcePath);
}
