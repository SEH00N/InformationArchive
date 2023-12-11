#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int coin, cost;
	std::cin >> coin >> cost;

	int* coins = new int[coin + 1];
	int* dp1 = new int[coin * (cost + 1)] {0};

	coins[0] = 0;
	std::unordered_map<int, int*> dp = std::unordered_map<int, int*>();
	
	for (int i = 1; i < coin; ++i)
		std::cin >> coins[i];

	for (int i = 1; i < coin; ++i)
	{
		int now = coins[i];
		int prev = coins[i - 1];

		for (int j = 0; j <= cost; ++j)
		{
			dp1[i * j]
		}
	}

	for (int i = 0; i < coin; ++i)
	{
		int now = coins[i];
		int prev = 0;
		if(i != 0)
			prev = coins[i - 1];

		for (int j = 1; j <= cost; ++j)
		{
			if (i != 0)
				dp[now][j] = dp[prev][j];
			else
				dp[now][j] = 0;

			if(j >= now) 
				dp[now][j] += dp[now][j - now];
		}
	}

	std::cout << dp[coins[coin - 1]][cost];

	return 0;
}