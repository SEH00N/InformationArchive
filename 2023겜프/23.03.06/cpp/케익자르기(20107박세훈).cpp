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
	//	if ((a > d && 0 < d) || (100 > d && d > b)) //c�� a, b ���̿� �ְ� d�� 0���� ũ�� a���� �۰ų� 100���� ������ b���� ū ��� (a�� �� ���� ����� ���� �Ͽ�)
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