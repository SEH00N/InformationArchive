#include <iostream>

long long container[1000]{ 1, 1 };

long long f(int n)
{
	if (n < 2)
		return 1;

	if (container[n] == 0)
		container[n] = 1 + f(n - 1) + f(n - 2);

	return container[n];
}

int main()
{
	while (true)
	{
		int i;
		std::cin >> i;
		std::cout << f(i) << '\n';
	}
	return 0;
}