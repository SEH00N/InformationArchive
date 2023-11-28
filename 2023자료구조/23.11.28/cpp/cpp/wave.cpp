#include <iostream>

long long dp[100] = { 1,1,1,2,2 };

long long wave(int i)
{
	if (i < 5)
		return dp[i];

	if (dp[i] == 0)
		dp[i] = wave(i - 1) + wave(i - 5);

	return dp[i];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;

	while (n--)
	{
		int i;
		std::cin >> i;
		std::cout << wave(i - 1) << '\n';
	}

	return 0;
}