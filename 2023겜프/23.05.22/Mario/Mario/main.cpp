#include <iostream>
#include "Core.h"

int main()
{
	if (Core::GetInstance()->Init())
	{
		std::cout << "Core 초기화 실패" << std::endl;
		Core::DestroyInstance();

		return 0;
	}

	Core::GetInstance()->Run();
	Core::DestroyInstance();

	return 0;
}