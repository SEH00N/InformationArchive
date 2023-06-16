#include <iostream>

int main()
{
	char prompt;
	int min, max, mid = -1;
	std::cout << "������ �ּ�, �ִ밪 �Է� : ";
	std::cin >> min >> max;

	std::cout << "���̰� �´ٸ� Y, �� ���ٸ� U, �� ���ٸ� D�� �Է��ϼ���." << std::endl;

	while (min + (max - min) / 2 != mid)
	{
		mid = min + (max - min) / 2;
		std::cout << mid << "�� �½��ϱ�? : ";
		std::cin >> prompt;

		if (prompt == 'Y' || prompt == 'y')
		{
			std::cout << "����";
			break;
		}
		else if (prompt == 'U' || prompt == 'u')
			min = mid;
		else if (prompt == 'D' || prompt == 'd')
			max = mid;
	}
	
	return 0;
}