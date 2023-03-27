#include <iostream>
//#include "BingoComponent.h"

using namespace std;

class Game
{
private:
	int iNumber[25] = {};
	int iBingo = 0;

public:
	int iInput = 0;

	void Init()
	{
		for (int i = 0; i < 25; i++)
			iNumber[i] = i + 1;

		int iTemp, idx1, idx2;
		for (int i = 0; i < 100; i++)
		{
			idx1 = rand() % 25;
			idx2 = rand() % 25;

			iTemp = iNumber[idx1];
			iNumber[idx1] = iNumber[idx2];
			iNumber[idx2] = iTemp;
		}
	}

	void CountBingo()
	{
		int iCheckBingo = 0;
		int iHorStar = 0, iVerStar = 0, iLTStar = 0, iRTStar = 0;

		for (int i = 0; i < 5; i++)
		{
			iHorStar = 0;
			iVerStar = 0;

			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					iHorStar++;
				if (iNumber[j * 5 + i] == INT_MAX)
					iVerStar++;
			}

			if (iHorStar == 5)
				iCheckBingo++;
			if (iVerStar == 5)
				iCheckBingo++;
		}

		for (int i = 0; i < 25; i += 6)
			if (iNumber[i] == INT_MAX)
				iLTStar++;
		if (iLTStar == 5)
			iCheckBingo++;

		for (int i = 4; i < 21; i += 4)
			if (iNumber[i] == INT_MAX)
				iRTStar++;
		if (iRTStar == 5)
			iCheckBingo++;

		this->iBingo = iCheckBingo;
	}

	void Update()
	{
		for (int i = 0; i < 25; i++)
			if (iInput == iNumber[i])
				iNumber[i] = INT_MAX;
	}
	
	void Render()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << '\t';
			}
			cout << '\n';
		}

		cout << "Bingo Line : " << iBingo << "\n\n";
	}

	bool IsChecked(int index)
	{
		return (this->iNumber[index] == INT_MAX);
	}

	bool CheckWin()
	{
		return iBingo >= 5;
	}
};

class AI
{
private:
	Game game;
public:
	void Init()
	{
		this->game.Init();
	}

	void DecideInput() // AI 난이도별 얘만 바꿔주면 댐
	{
		while(true)
		{
			this->game.iInput = rand() % 25;

			if (this->game.IsChecked(this->game.iInput) == false)
				break;
		}
	}

	void ApplyInput()
	{
		this->game.Update();
		this->game.CountBingo();
	}

	Game GetGame()
	{
		return this->game;
	}
};

void RenderNumber(Game player1, Game player2)
{
	cout << "======================\n";
	cout << "|      빙고게임      |\n";
	cout << "=============================================\n";
	cout << "빙고줄이 5줄 이상이 되면 게임에서 승리합니다.\n";
	cout << "=============================================\n";
	
	cout << "\nPlayer1 빙고판\n";
	player1.Render();

	cout << "\nPlayer2 빙고판\n";
	player2.Render();
}

bool CheckEnd(Game player1, Game player2)
{
	if (player1.CheckWin() && player2.CheckWin())
	{
		cout << "무승부입니다! \n";
		return true;
	}
	else if (player1.CheckWin())
	{
		cout << "1번 플레이어가 게임에서 승리하였습니다. \n";
		return true;
	}
	else if (player2.CheckWin())
	{
		cout << "2번 플레이어가 게임에서 승리하였습니다. \n";
		return true;
	}
	else
		return false;
}

int main()
{
	Game player;
	AI ai;
	
	srand((unsigned int)time(NULL));
	player.Init();
	ai.Init();

	while (true)
	{
		system("cls");
		RenderNumber(player, ai.GetGame());

		CheckEnd(player, ai.GetGame());
		
		cout << "숫자를 입력하세요. (0 : 종료)\n";
		cin >> player.iInput;

		if (player.iInput == 0)
		{
			cout << "게임을 종료합니다.\n";
			break;
		}
		else if (player.iInput < 1 || player.iInput > 25)
		{
			cout << "잘못입력하셨습니다. 올바른 수를 입력해주세요. \n";
			continue;
		}

		player.Update();
		player.CountBingo();

		ai.DecideInput();
		ai.ApplyInput();
	}

	return 0;
}