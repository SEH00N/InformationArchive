#include <iostream>
#include "Core.h"

int main()
{
	if (Core::GetInstance()->Init())
	{
		std::cout << "Core �ʱ�ȭ ����" << std::endl;
		Core::DestroyInstance();

		return 0;
	}

	Core::GetInstance()->Run();
	Core::DestroyInstance();

	return 0;
}