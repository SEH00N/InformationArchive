#include <iostream>
#include<windows.h>
#include <string>

using namespace std;

void mswap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void mswap(int* x, int* y)
{
	int* temp = x;
	x = y;
	y = temp;
}

void msswap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

int main()
{
#pragma region Multiply

	//int x, i = 0, arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//cout << "����� ����Ͻðڽ��ϱ�? : ";
	//cin >> x;

	//for (int i = 0; i < 9; i++)
	//	cout << x << " * " << i + 1 << " = " << x * (i + 1) << '\n';

	//cout << '\n';


	//while (i < 9)
	//{
	//	cout << x << " * " << i + 1 << " = " << x * (i + 1) << '\n';
	//	i++;
	//}

	//i = 0;
	//cout << '\n';

	//do
	//{
	//	cout << x << " * " << i + 1 << " = " << x * (i + 1) << '\n';
	//	i++;
	//} while (i < 9);

	//cout << '\n';

	//for(int i : arr)
	//	cout << x << " * " << i << " = " << x * i << '\n';

#pragma endregion

#pragma region Counting

	//cout << "�����ڸ� �Է��ϰ� ctrl + z�� �Է��ϼ���" << '\n';
	//int consonant = 0, vowel = 0;
	//char letter;
	//
	//while (true)
	//{
	//	cin >> letter;

	//	if (cin.eof())
	//		break;
	//	
	//	letter = tolower(letter);
	//	if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u')
	//		vowel++;
	//	else
	//		consonant++;
	//}

	//cout << "���� : " << vowel << '\n';
	//cout << "���� : " << consonant;

#pragma endregion

#pragma region Up & Down 

	//srand((unsigned int)time(NULL));

	//int input, tryCnt = 0, randomNum = rand() % 100 + 1;

	//while (true)
	//{
	//	tryCnt++;
	//	cout << "������ �����Ͽ� ���ÿ� : ";
	//	cin >> input;

	//	if (input == randomNum)
	//	{
	//		cout << "����!! �õ�Ƚ�� : " << tryCnt;
	//		break;
	//	}
	//	else
	//		cout << (input > randomNum ? "�ٿ�!" : "��!") << '\n';
	//}

#pragma endregion

#pragma region Random Math Teacher

	/*int x, y, answer, cnt, prefix, right = 0;
	bool correct;
	char prefixes[] = { '+', '*', '-', '/' };
	clock_t start, end;

	cout << "1 ~ 100 ������ ���� �̷���� ��Ģ���� ������ �����մϴ�. (�������� ��� �Ҽ����� �����մϴ�.)\n";
	cout << "������ ������ �Է����ּ��� : ";

	cin >> cnt;

	cout << '\n';

	start = clock();

	for (int i = 0; i < cnt; i++)
	{
		srand((unsigned int)time(NULL));
		x = rand() % 100 + 1;
		y = rand() % 100 + 1;

		prefix = prefixes[rand() % 4];

		cout << x << ' ' << (char)prefix << ' ' << y << " = ";
		cin >> answer;

		switch (prefix)
		{
		case '+':
			correct = answer == x + y;
			break;
		case '-':
			correct = answer == x - y;
			break;
		case '*':
			correct = answer == x * y;
			break;
		case '/':
			correct = answer == x / y;
			break;
		default:
			break;
		}

		if (correct)
		{
			cout << "����!\n";
			right++;
		} else
		cout << "����\n";
	}

	end = clock();

	cout << '\n';
	cout << "���� ���� : " << right << '\n';
	cout << "���� ���� : " << cnt - right << "\n\n";
	cout << "�ɸ��ð� : " << (end - start) / 1000 << "��";*/

#pragma endregion

#pragma region Swap

	//int x = 1;
	//int y = 3;

	//cout << x << ' ' << y << '\n';

	//mswap(&x, &y);

	//cout << x << ' ' << y << '\n';
	//
	//msswap(x, y);
	//
	//cout << x << ' ' << y << '\n';

#pragma endregion



	return 0;
}