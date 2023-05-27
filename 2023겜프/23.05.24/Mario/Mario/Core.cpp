#include <iostream>
#include <windows.h>
#include "Core.h"
#include "MapManager.h"

Core* Core::instance = nullptr;

Core::Core()
{

}

bool Core::Init()
{
	// Manager Initialize
	// Cursor Remove

	if (!MapManager::GetInstance()->Init())
		return false;

	return true;
}

void Core::Run()
{
	int stage = MenuDraw();

	while (true)
	{
		MapManager::GetInstance()->Run(stage);
	}
}

int Core::MenuDraw()
{
	std::cout << "1. Stage1 " << std::endl;
	std::cout << "2. Stage2 " << std::endl;
	std::cout << "3. Stage3 " << std::endl;
	std::cout << "4. Exit " << std::endl;

	int input;
	std::cin >> input;

	return input;
}
