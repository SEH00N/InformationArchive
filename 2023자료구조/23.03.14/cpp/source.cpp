#include <iostream>
#include <vector>

using namespace std;

int main()
{
#pragma region Find Max Value

	//int max = 0, arr[100];

	//srand((unsigned int)time(NULL));

	//for (int i = 0; i < 100; i++)
	//{
	//	arr[i] = rand() % 100 + 1;
	//	if (arr[i] > max)
	//		max = arr[i];
	//}

	//cout << "최대값 = " << max;
		
#pragma endregion

#pragma region Tic Tac toe

	//int x, y, turn = 0;
	//char arr[3][3];
	//bool is_end = false;


	////for (int i = 0; i < 3; i++)
	////	for (int j = 0; j < 3; j++)
	////		arr[i][j] = ' ';

	//fill(&arr[0][0], &arr[2][2] + 1, ' ');

	//while (is_end == false)
	//{
	//	turn++;

	//	cout << (turn - 1) % 2 + 1 << "번 플레이어 차례\n(x, y) 좌표 : ";
	//	cin >> x >> y;

	//	cout << '\n';

	//	if (x < 0 || x > 2 || y < 0 || y > 3)
	//	{
	//		cout << "잘못된 수를 입력했습니다. 다시 입력해주세요.\n\n";
	//		turn--;
	//		continue;
	//	}
	//	else if (arr[x][y] != ' ')
	//	{
	//		cout << "이미 채워진 칸입니다. 다시 입력해주세요.\n\n";
	//		turn--;
	//		continue;
	//	}

	//	arr[x][y] = (turn % 2 == 1) ? 'x' : 'o';
	//	cout << "|---|---|---|\n";
	//	cout << "| " << arr[0][0] << " | "<< arr[0][1] << " | "<< arr[0][2] << " |\n";
	//	cout << "|---|---|---|\n";
	//	cout << "| "<< arr[1][0] << " | "<< arr[1][1] << " | "<< arr[1][2] << " |\n";
	//	cout << "|---|---|---|\n";
	//	cout << "| "<< arr[2][0] << " | "<< arr[2][1] << " | "<< arr[2][2] << " |\n";
	//	cout << "|---|---|---|\n\n";
	//}

#pragma endregion

#pragma region vector

	vector<int> v;

	for (int i = 0; i < 1000; i++)
	{
		v.push_back(100);
		cout << v.size() << ' ' << v.capacity() << '\n';
	}

	vector<string> str_v;
	str_v.resize(100);

	for (int i = 0; i < str_v.size(); i++)
		cout << str_v[i] << ", ";

#pragma endregion


	return 0;
}