#include <iostream>
#include <windows.h>

using namespace std;

void Init(int* _pNumber)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 25; i++)
		_pNumber[i] = i + 1;

	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = _pNumber[idx1];
		_pNumber[idx1] = _pNumber[idx2];
		_pNumber[idx2] = iTemp;
	}
}

void RenderNumber(int* _pNumber, int _iBingo)
{
	cout << "======================\n";
	cout << "|      빙고게임      |\n";
	cout << "=============================================\n";
	cout << "빙고줄이 5줄 이상이 되면 게임에서 승리합니다.\n";
	cout << "=============================================\n";

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_pNumber[i * 5 + j] == INT_MAX)
				cout << "*\t";
			else
				cout << _pNumber[i * 5 + j] << '\t';
		}
		cout << '\n';
	}

	cout << "Bingo Line : " << _iBingo << '\n';
}

void Update(int* _pNumber, int& _iInput)
{
	for (int i = 0; i < 25; i++)
	{
		if (_iInput == _pNumber[i])
		{
			_pNumber[i] = INT_MAX;
		}
	}
}

int CountBingo(int* _pNumber)
{
	int iCheckBingo = 0;
	int iHorStar = 0, iVerStar = 0, iLTStar = 0, iRTStar = 0;

	for (int i = 0; i < 5; i++)
	{
		iHorStar = 0;
		iVerStar = 0;

		for (int j = 0; j < 5; j++)
		{
			if (_pNumber[i * 5 + j] == INT_MAX)
				iHorStar++;
			if (_pNumber[j * 5 + i] == INT_MAX)
				iVerStar++;
		}

		if (iHorStar == 5)
			iCheckBingo++;
		if (iVerStar == 5)
			iCheckBingo++;
	}

	for (int i = 0; i < 25; i += 6)
		if (_pNumber[i] == INT_MAX)
			iLTStar++;
	if (iLTStar == 5)
		iCheckBingo++;

	for (int i = 4; i < 21; i += 4)
		if (_pNumber[i] == INT_MAX)
			iRTStar++;
	if (iRTStar == 5)
		iCheckBingo++;

	return iCheckBingo;
}

int main()
{
	int iNumber[25] = {};
	int iBingo = 0;
	int iInput;

	Init(iNumber);
	
	while (true)
	{
		system("cls");
		RenderNumber(iNumber, iBingo);

		if (iBingo >= 5)
		{
			cout << "게임에서 승리하셨습니다.\n";
			break;
		}

		cout << "숫자를 입력하세요. (0 : 종료)\n";
		cin >> iInput;

		if (iInput == 0)
		{
			cout << "게임을 종료합니다.\n";
			break;
		}
		else if (iInput < 1 || iInput > 25)
		{
			cout << "잘못입력하셨습니다. 올바른 수를 입력해주세요. \n";
			continue;
		}

		Update(iNumber, iInput);
		iBingo = CountBingo(iNumber);
	}

	return 0;
}