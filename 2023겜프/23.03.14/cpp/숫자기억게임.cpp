#include <iostream>
#include <windows.h>

using namespace std;

const int MILLISEC = 1000;

enum MODE
{
	EASY = 1,
	NORMAL = 2,
	HARD = 3,
};

void printRandInt(int cnt, int delay, int* arr);
void readNumbers(int cnt, int* answer);

int main()
{
	cout << "---------------------------\n";
	cout << "   난이도를 입력해주세요.\n";
	cout << "EASY: 1, NORMAL: 2, HARD: 3\n";
	cout << "---------------------------\n";

	int mode, delay;

	cin >> mode;

	int* numbers = new int[mode * 5];

	switch (mode)
	{
	case EASY:
		delay = 1 * MILLISEC;
		break;
	case NORMAL:
		delay = 0.7f * MILLISEC;
		break;
	case HARD:
		delay = 0.5f * MILLISEC;
		break;
	default:
		break;
	}

	printRandInt(mode * 5, delay, numbers);
	readNumbers(mode * 5, numbers);

	return 0;
}

void printRandInt(int cnt, int delay, int* arr)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < cnt; i++)
	{
		arr[i] = rand() % 100 + 1;
		cout << arr[i] << ' ';
		Sleep(delay);
	}
}

void readNumbers(int cnt, int* answer)
{
	int temp;

	for (int i = 0; i < cnt; i++)
	{
		cin >> temp;
		if (temp != answer[i])
		{
			cout << '땡';
			break;
		}
	}
}