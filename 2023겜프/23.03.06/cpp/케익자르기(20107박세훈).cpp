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
			if ((a > d && 0 < d) || (100 > d && d > b)) //c�� a, b ���̿� �ְ� d�� 0���� ũ�� a���� �۰ų� 100���� ������ b���� ū ��� (a�� �� ���� ����� ���� �Ͽ�)
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