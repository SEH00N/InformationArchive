#include <iostream>
#include <vector>

long long container[1000];

long long f(int i)
{
	if (i == 0)
		return 0;
	else if (i == 1 || i == 2)
		return 1;

	if (container[i] == -1)
		container[i] = f(i - 1) + f(i - 2);

	return container[i];
}

int main()
{
	std::fill(container, container + 1000, -1);
	while (true)
	{
		int i;
		std::cin >> i;
		std::cout << f(i);
	}
	return 0;
}