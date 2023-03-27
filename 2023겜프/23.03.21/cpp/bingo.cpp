#include <iostream>
#include <windows.h>

using namespace std;

enum class AI_MODE
{
	AM_EASY = 1,
	AM_NORMAL
};

enum class LINE_NUMBER
{
	LN_H1, LN_H2, LN_H3, LN_H4, LN_H5,
	LN_V1, LN_V2, LN_V3, LN_V4, LN_V5,
	LN_LT, LN_RT
};

void Init(int* _pNumber)
{
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

AI_MODE SelectAiMode()
{
	cout << "======================\n";
	cout << "|      빙고게임      |\n";
	cout << "=============================================\n";
	cout << "빙고줄이 5줄 이상이 되면 게임에서 승리합니다.\n";
	cout << "=============================================\n";

	cout << "1. Easy\n";
	cout << "2. Normal\n";
	cout << "=============================================\n";

	int iAiMode;
	cin >> iAiMode;

	if (iAiMode < (int)AI_MODE::AM_EASY || iAiMode >(int)AI_MODE::AM_NORMAL)
	{
		cout << "잘못 입력하셨습니다.\n";
		system("cls");

		SelectAiMode();
	}

	return (AI_MODE)iAiMode;
}

int SelectAiNumber(int* _pNumber, AI_MODE _eMode)
{
	int iNoneSelect[25] = {};
	int iNoneSelectcnt = 0;

	switch (_eMode)
	{
	case AI_MODE::AM_EASY:
	{
		for (int i = 0; i < 25; i++)
		{
			if (_pNumber[i] != INT_MAX)
			{
				iNoneSelect[iNoneSelectcnt] = _pNumber[i];
				++iNoneSelectcnt;
			}
		}

		return iNoneSelect[rand() % iNoneSelectcnt];
	}
	break;
	case AI_MODE::AM_NORMAL:
	{
		int iLine = 0;
		int iStarcnt = 0;
		int iSavecnt = 0;

		for (int i = 0; i < 5; ++i)
		{
			iStarcnt = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (_pNumber[i * 5 + j] == INT_MAX)
					iStarcnt++;
			}

			if (iStarcnt < 5 && iStarcnt > iSavecnt)
			{
				iLine = i;
				iSavecnt = iStarcnt;
			}
		}

		for (int i = 0; i < 5; ++i)
		{
			iStarcnt = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (_pNumber[j * 5 + i] == INT_MAX)
					iStarcnt++;
			}

			if (iStarcnt < 5 && iStarcnt > iSavecnt)
			{
				iLine = i + 5;
				iSavecnt = iStarcnt;
			}
		}
	
		iStarcnt = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (_pNumber[i] == INT_MAX)
				iStarcnt++;
		}

		if (iStarcnt < 5 && iStarcnt > iSavecnt)
		{
			iLine = (int)LINE_NUMBER::LN_LT;
			iSavecnt = iStarcnt;
		}

		iStarcnt = 0;
		for (int i = 0; i < 21; i += 4)
		{
			if (_pNumber[i] == INT_MAX)
				iStarcnt++;
		}

		if (iStarcnt < 5 && iStarcnt > iSavecnt)
		{
			iLine = (int)LINE_NUMBER::LN_RT;
			iSavecnt = iStarcnt;
		}

		if (iLine <= (int)LINE_NUMBER::LN_H5)
		{
			for (int i = 0; i < 5; ++i)
				if (_pNumber[iLine * 5 + i] != INT_MAX)
					return iLine * 5 + i;
		}
		else if (iLine <= (int)LINE_NUMBER::LN_V5)
		{
			for (int i = 0; i < 5; ++i)
				if (_pNumber[i * 5 + (iLine - 5)] != INT_MAX)
					return i * 5 + (iLine - 5);
		}
		else if (iLine <= (int)LINE_NUMBER::LN_LT)
		{
			for (int i = 0; i < 25; i += 6)
				if (_pNumber[i] != INT_MAX)
					return i;
		}
		else if (iLine <= (int)LINE_NUMBER::LN_RT)
		{
			for (int i = 0; i < 21; i += 4)
				if (_pNumber[i] != INT_MAX)
					return i;
		}
	}
	break;
	}

	return -1;
}

int main()
{
	srand((unsigned int)time(NULL));

	int iNumber[25] = {};
	int iAiNumber[25] = {};
	int iBingo = 0;
	int iAiBingo = 0;
	int iInput;

	Init(iNumber);
	Init(iAiNumber);

	AI_MODE eAiMode = SelectAiMode();

	while (true)
	{
		system("cls");
		cout << "========== Plyer ==========\n";
		RenderNumber(iNumber, iBingo);
		cout << "========== AI ==========\n";

		switch (eAiMode)
		{
		case AI_MODE::AM_EASY:
			cout << "AImode : EASY\n";
			break;
		case AI_MODE::AM_NORMAL:
			cout << "AImode : NORMAL\n";
			break;
		default:
			break;
		}
		RenderNumber(iAiNumber, iAiBingo);

		if (iBingo >= 5)
		{
			cout << "게임에서 승리하셨습니다.\n";
			break;
		}
		if (iAiBingo >= 5)
		{
			cout << "게임에서 패배하셨습니다.\n";
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
		Update(iAiNumber, iInput);

		iInput = SelectAiNumber(iAiNumber, eAiMode);
		cout << "AI가 선택한 숫자는 " << iInput << "입니다.\n";
		Sleep(1000);

		Update(iNumber, iInput);
		Update(iAiNumber, iInput);

		iBingo = CountBingo(iNumber);
		iAiBingo = CountBingo(iAiNumber);
	}

	return 0;
}