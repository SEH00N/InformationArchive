#include <iostream>

using namespace std;

int SWAP(int& a, int& b)
{
	int temp = a;
	a = b;
	b = a;
}

int SWAP(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	int a = 3, b = 5;

	cout << a << ' ' << b;
	SWAP(a, b);
	cout << a << ' ' << b;
	SWAP(&a, &b);
	cout << a << ' ' << b;
}