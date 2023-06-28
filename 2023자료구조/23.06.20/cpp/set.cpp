#include <iostream>
#include <set>

int main()
{
	std::set<int> set;
	int count, num;

	std::cin >> count;

	for (int i = 0; i < count; ++i)
	{
		std::cin >> num;
		set.insert(num);
	}

	std::cin >> count;

	for (int i = 0; i < count; ++i)
	{
		std::cin >> num;
		if (set.find(num) != set.end())
			std::cout << "1 ";
		else
			std::cout << "0 ";
	}

	return 0;
}