#include <iostream>
#include <vector>

using namespace std;

void SWAP(int& a, int& b)
{
	int temp = a;
	a = b;
	b = a;
}

void SWAP(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

long long binary(int num)
{
	if (num < 2)
		return num;

	return binary(num / 2) * 10 + num % 2;
}

int main()
{
	int a = 3, b = 5;

	cout << a << ' ' << b << endl;
	SWAP(a, b);
	cout << a << ' ' << b << endl;
	SWAP(&a, &b);
	cout << a << ' ' << b << endl;

	cout << endl;

	string str = "I love c++";
	cout << str << endl;
	cout << "++이 시작되는 인덱스 : " << str.find("++") << endl;
	cout << str.erase(str.find("++")) << endl;
	cout << str.append("#") << endl;

	cout << endl;

	vector<int> vec { 1,3,4,5,6 };
	vec.push_back(7);
	vec.erase(vec.end() - 1);

	cout << vec[0] << endl;
	cout << vec[vec.size() - 1] << endl;
	cout << vec.size() << endl;

	vec.insert(vec.begin() + 1, 2);
	vec.erase(vec.begin() + 1, vec.begin() + 2);

	cout << endl;

	int arr[8] = {};
	fill(arr, arr + 3, 1);
	
	int* ptr = arr;
	cout << ptr[2] << endl;

	cout << endl;

	int grid[9][9], max = -1, x, y;

	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			cin >> grid[j][i];

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (grid[j][i] > max)
			{
				max = grid[j][i];
				x = i;
				y = j;
			}
		}
	}

	cout << max << endl;
	cout << x + 1 << ' ' << y + 1 << endl;

	cout << endl;
	
	int temp;

	for (int i = 0; i < 3; ++i)
	{
		cout << "10진수 값을 입력하세요 : ";
		cin >> temp;
		cout << "2진수로 변환한 값 : " << binary(temp) << endl;
	}
}