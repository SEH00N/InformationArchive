#include <iostream>
#include <algorithm>

long long dp[10000] = { 0, 1, 2, 3, 1, 1 };

int main()
{
    int n;
    std::cin >> n;

    for (int i = 6; i <= n; ++i)
        dp[i] = std::min(std::min(dp[i - 1], dp[i - 4]), dp[i - 5]) + 1;
    
    std::cout << dp[n];
}