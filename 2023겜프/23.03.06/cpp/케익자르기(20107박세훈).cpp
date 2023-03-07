#include <iostream>

using namespace std;

int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	if (a > b)
	{
		int temp = b;
		b = a;
		a = temp;
	}

	//if (a < c && c < b)
	//{
	//	if (b < d && d > a)
	//		cout << "cross";
	//	else
	//		cout << "not cross";
	//}
	//else
	//{
	//	if (a < d && d < b)
	//		cout << "cross";
	//	else
	//		cout << "not cross";
	//}

	//if (a < c && c < b)
	//{
	//	if ((a > d && 0 < d) || (100 > d && d > b)) //c가 a, b 사이에 있고 d가 0보다 크고 a보다 작거나 100보다 작으며 b보다 큰 경우 (a가 더 작은 수라는 가정 하에)
	//		cout << "cross";
	//	else 
	//		cout << "not cross";
	//}
	//else if (a < d && d < b)
	//{
	//	if ((a > c && 0 < c) || (100 > c && c > b))
	//		cout << "cross";
	//	else
	//		cout << "not cross";
	//}

	cout << endl;

	return 0;
}