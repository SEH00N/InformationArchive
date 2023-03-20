#include <iostream>
#include <conio.h>
#include "퍼즐게임cpp.h"

using namespace std;

void Init(int* pNumber)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 24; i++)
		pNumber[i] = i + 1;

	pNumber[24] = INT_MAX;

	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = pNumber[idx1];
		pNumber[idx1] = pNumber[idx2];
		pNumber[idx2] = iTemp;
	}
}

void RenderNumber(int* pNumber)
{
	cout << "=====================\n";
	cout << "|   숫자 퍼즐 게임   |\n";
	cout << "=====================\n";
	cout << "* 을 움직여서 1 ~ 24까지 퍼즐을 맞춰보세요.\n";
	cout << "=====================\n";

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (pNumber[i * 5 + j] == INT_MAX)
				cout << "*\t";
			else
				cout << pNumber[i * 5 + j] << '\t';
		}
		cout << '\n';
	}
}

char Update(int* pNumber)
{
	cout << "w : 위, s : 아래, a : 왼쪽, d : 오른쪽, q : 종료\n";
	static int iStartIndex = 24;
	char cInput = _getch();

	switch (cInput)
	{
	case 'w':
	case 'W':
	{
		if (iStartIndex > 4)
		{
			pNumber[iStartIndex] = pNumber[iStartIndex - 5];
			pNumber[iStartIndex - 5] = INT_MAX;
			iStartIndex -= 5;
		}
	}
		break;
	case 's':
	case 'S':
	{
		if (iStartIndex < 20)
		{
			pNumber[iStartIndex] = pNumber[iStartIndex + 5];
			pNumber[iStartIndex + 5] = INT_MAX;
			iStartIndex += 5;
		}
	}
		break;
	case 'a':
	case 'A':
	{
		if (iStartIndex % 5 != 0)
		{
			pNumber[iStartIndex] = pNumber[iStartIndex - 1];
			pNumber[iStartIndex - 1] = INT_MAX;
			iStartIndex -= 1;
		}
	}
		break;
	case 'd':
	case 'D':
	{
		if (iStartIndex % 5 != 4)
		{
			pNumber[iStartIndex] = pNumber[iStartIndex + 1];
			pNumber[iStartIndex + 1] = INT_MAX;
			iStartIndex += 1;
		}
	}
		break;
	}

	return cInput;
}

void PuzzleCheck(int* pNumber)
{
	bool bChk = true;

	for (int i = 0; i < 24; i++)
	{
		if (pNumber[i] != i + 1)
		{
			bChk = false;
			break;
		}
	}

	if (bChk)
	{
		cout << "숫자 다 맞췄습니다. \n";
		return;
	}
}

int main()
{
	int iNumber[25] = {};

	Init(iNumber);

	while (true)
	{
		system("cls");
		RenderNumber(iNumber);
		PuzzleCheck(iNumber);
		char cChk = Update(iNumber);

		if (cChk == 'q' || cChk == 'Q')
			break;
	}

	return 0;
}