#include <iostream>

using namespace std;

int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	bool isCross = false;

	if (a > b)
	{
		int temp = b;
		b = a;
		a = temp;
	}

	if (a < b)
	{
		if (a < c && c < b)
		{
			if ((a > d && 0 < d) || (100 > d && d > b)) //c가 a, b 사이에 있고 d가 0보다 크고 a보다 작거나 100보다 작으며 b보다 큰 경우 (a가 더 작은 수라는 가정 하에)
				isCross = true;
		}
		else if (a < d && d < b)
		{
			if ((a > c && 0 < c) || (100 > c && c > b))
				isCross = true;
		}
	}

	cout << (isCross ? "cross" : "not cross");
	cout << endl;

	return 0;
}