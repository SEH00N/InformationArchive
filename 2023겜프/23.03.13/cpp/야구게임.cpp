#include <iostream>
#include <Windows.h>

using namespace std;

bool includes(int arr[], int target, int range)
{
	for (int i = 0; i < range; i++)
		if (arr[i] == target)
			return true;

	return false;
}

int main()
{
	int idx1, idx2, temp, numbers[9] = {};

	for (int i = 0; i < sizeof(numbers) / sizeof(int); i++)
		numbers[i] = i + 1;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		//cout << idx1 << ' ' << idx2 << '\n';
		temp = numbers[idx1];
		numbers[idx1] = numbers[idx2];
		numbers[idx2] = temp;
	}

	cout << numbers[0] << "\t" << numbers[1] << "\t" << numbers[2] << '\n';

	int iStrike = 0, iBall = 0, iCnt = 0, iInput[3] = {};

	while (true)
	{
		iStrike = 0;
		iBall = 0;
		iCnt++;

		cout << iCnt << " 회\n";
		cout << "1 ~ 9 숫자 중 숫자 3개를 입력하세요. (0 : 종료) : ";
		cin >> iInput[0] >> iInput[1] >> iInput[2];

		if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0)
			break;
		else if (iInput[0] < 1 || iInput[0] > 9 || iInput[1] < 1 || iInput[1] > 9 || iInput[2] < 1 || iInput[2] > 9)
		{
			cout << "잘못 된 숫자를 입력하였습니다. 1 ~ 9 범위의 숫자를 입력하세요. \n";
			continue;
		}
		else if (iInput[0] == iInput[1] || iInput[1] == iInput[2] || iInput[0] == iInput[2])
		{
			cout << "중복된 숫자를 입력하였습니다. 잘하자 \n";
			continue;
		}

		/*for (int i = 0; i < 3; i++)
		{
			if (numbers[i] == iInput[i])
				iStrike++;
			else if (includes(numbers, iInput[i], 3))
				iBall++;
		}*/

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (numbers[i] == iInput[j])
				{
					if (i == j)
						iStrike++;
					else
						iBall++;
				}
			}
		}

		if (iStrike == 3)
		{
			Sleep(0.25f * 1000);

			cout << "!!!!!";

			Sleep(1 * 1000);

			system("cls");
			cout << "숫자를 모두 맞췄습니다. 축하합니당\n";

			break;
		}
		else if (iStrike == 0 && iBall == 0)
			cout << "Out!!\n";
		else
			cout << iStrike << " STRIKE | " << iBall << " BALL\n";
	}

	/*for (int i = 0; i < sizeof(numbers) / sizeof(int); i++)
	{
		srand((unsigned int)time(NULL));
		while (true)
		{
			temp = rand() % 10 + 1;
			if (!includes(numbers, temp, i))
				break;
		}

		numbers[i] = temp;
		cout << temp << '\n';
	}*/

	return 0;
}