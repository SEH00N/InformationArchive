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
	//cout << "몇단을 출력하시겠습니까? : ";
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

	//cout << "영문자를 입력하고 ctrl + z를 입력하세요" << '\n';
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

	//cout << "모음 : " << vowel << '\n';
	//cout << "자음 : " << consonant;

#pragma endregion

#pragma region Up & Down 

	//srand((unsigned int)time(NULL));

	//int input, tryCnt = 0, randomNum = rand() % 100 + 1;

	//while (true)
	//{
	//	tryCnt++;
	//	cout << "정답을 추측하여 보시오 : ";
	//	cin >> input;

	//	if (input == randomNum)
	//	{
	//		cout << "정답!! 시도횟수 : " << tryCnt;
	//		break;
	//	}
	//	else
	//		cout << (input > randomNum ? "다운!" : "업!") << '\n';
	//}

#pragma endregion

#pragma region Random Math Teacher

	/*int x, y, answer, cnt, prefix, right = 0;
	bool correct;
	char prefixes[] = { '+', '*', '-', '/' };
	clock_t start, end;

	cout << "1 ~ 100 사이의 수로 이루어진 사칙연산 문제를 생성합니다. (나눗셈의 경우 소수점을 생략합니다.)\n";
	cout << "문제의 개수를 입력해주세요 : ";

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
			cout << "정답!\n";
			right++;
		} else
		cout << "오답\n";
	}

	end = clock();

	cout << '\n';
	cout << "정답 개수 : " << right << '\n';
	cout << "오답 개수 : " << cnt - right << "\n\n";
	cout << "걸린시간 : " << (end - start) / 1000 << "초";*/

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