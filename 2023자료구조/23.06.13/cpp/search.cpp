#include <iostream>

int main()
{
	char prompt;
	int min, max, mid = -1;
	std::cout << "나이의 최소, 최대값 입력 : ";
	std::cin >> min >> max;

	std::cout << "나이가 맞다면 Y, 더 많다면 U, 더 적다면 D을 입력하세요." << std::endl;

	while (min + (max - min) / 2 != mid)
	{
		mid = min + (max - min) / 2;
		std::cout << mid << "이 맞습니까? : ";
		std::cin >> prompt;

		if (prompt == 'Y' || prompt == 'y')
		{
			std::cout << "정답";
			break;
		}
		else if (prompt == 'U' || prompt == 'u')
			min = mid;
		else if (prompt == 'D' || prompt == 'd')
			max = mid;
	}
	
	return 0;
}