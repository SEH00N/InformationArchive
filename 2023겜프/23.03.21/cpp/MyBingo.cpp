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

	void DecideInput() // AI ���̵��� �길 �ٲ��ָ� ��
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
	cout << "|      �������      |\n";
	cout << "=============================================\n";
	cout << "�������� 5�� �̻��� �Ǹ� ���ӿ��� �¸��մϴ�.\n";
	cout << "=============================================\n";
	
	cout << "\nPlayer1 ������\n";
	player1.Render();

	cout << "\nPlayer2 ������\n";
	player2.Render();
}

bool CheckEnd(Game player1, Game player2)
{
	if (player1.CheckWin() && player2.CheckWin())
	{
		cout << "���º��Դϴ�! \n";
		return true;
	}
	else if (player1.CheckWin())
	{
		cout << "1�� �÷��̾ ���ӿ��� �¸��Ͽ����ϴ�. \n";
		return true;
	}
	else if (player2.CheckWin())
	{
		cout << "2�� �÷��̾ ���ӿ��� �¸��Ͽ����ϴ�. \n";
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
		
		cout << "���ڸ� �Է��ϼ���. (0 : ����)\n";
		cin >> player.iInput;

		if (player.iInput == 0)
		{
			cout << "������ �����մϴ�.\n";
			break;
		}
		else if (player.iInput < 1 || player.iInput > 25)
		{
			cout << "�߸��Է��ϼ̽��ϴ�. �ùٸ� ���� �Է����ּ���. \n";
			continue;
		}

		player.Update();
		player.CountBingo();

		ai.DecideInput();
		ai.ApplyInput();
	}

	return 0;
}