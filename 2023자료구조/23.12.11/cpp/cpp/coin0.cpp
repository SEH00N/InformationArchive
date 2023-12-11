#include <iostream>
#include <algorithm>

int main()
{
	int coin, cost, answer = 0;
	std::cin >> coin >> cost;

	int* coins = new int[coin];
	for (int i = 0; i < coin; ++i)
		std::cin >> coins[i];

	std::sort(coins, coins + coin, std::greater<int>());

	for (int i = 0; i < coin; ++i)
	{
		if (cost <= 0)
			continue;

		int divide = cost / coins[i];
		
		answer += divide;
		cost %= coins[i];
	}

	std::cout << answer;

	return 0;
}