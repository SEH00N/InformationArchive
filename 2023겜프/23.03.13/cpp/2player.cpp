#include <iostream>
#include <windows.h>

using namespace std;

int iInput[3], q[6], iStrike, iBall, iCnt = 0;

bool scoring(int player);
void checkAnswer(int factor);
int input(int player);

int main()
{
	int iTemp;

	cout << "1번 플레이어가 맞출 번호를 입력해주세요 : ";
	cin >> q[0] >> q[1] >> q[2];

	system("cls");

	cout << "2번 플레이어가 맞출 번호를 입력해주세요 : ";
	cin >> q[3] >> q[4] >> q[5];

	system("cls");

	while (true)
	{
		iCnt++;
		iStrike = iBall = 0;

		iTemp = input((iCnt - 1) % 2 + 1);
		if (iTemp == 0)
			break;
		else if (iTemp == 1)
			continue;
		
		checkAnswer((iCnt - 1) % 2);
		if (scoring((iCnt - 1) % 2 + 1))
			break;
	}

	return 0;
}

bool scoring(int player)
{
	if (iStrike == 3)
	{
		Sleep(0.25f * 1000);

		cout << "!!!!!";

		Sleep(1 * 1000);

		system("cls");
		cout << player << "번 플레이어가 숫자를 모두 맞췄습니다. 축하합니당\n";

		return true;
	}
	else if (iStrike == 0 && iBall == 0)
		cout << "Out!!\n";
	else
		cout << iStrike << " STRIKE | " << iBall << " BALL\n";

	return false;
}

void checkAnswer(int factor)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (q[i + factor * 3] == iInput[j])
			{
				if (i == j)
					iStrike++;
				else
					iBall++;
			}
		}
	}
}

int input(int player)
{
	cout << player << "번 플레이어 " << ceil(iCnt * 0.5f) << " 회\n";
	cout << "1 ~ 9 숫자 중 숫자 3개를 입력하세요. (0 : 종료) : ";
	cin >> iInput[0] >> iInput[1] >> iInput[2];

	if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0)
		return 0;
	else if (iInput[0] < 1 || iInput[0] > 9 || iInput[1] < 1 || iInput[1] > 9 || iInput[2] < 1 || iInput[2] > 9)
	{
		cout << "잘못 된 숫자를 입력하였습니다. 1 ~ 9 범위의 숫자를 입력하세요. \n";
		return 1;
	}
	else if (iInput[0] == iInput[1] || iInput[1] == iInput[2] || iInput[0] == iInput[2])
	{
		cout << "중복된 숫자를 입력하였습니다. 잘하자 \n";
		return 1;
	}

	return 2;
}