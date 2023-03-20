#include <iostream>
#include <conio.h>

using namespace std;

void gameInit()
{
	cout << "=================\n";
	cout << "| 시간맞히기게임 |\n";
	cout << "=================\n";
	cout << "============================================================\n";
	cout << "설명 : 시간을 재는 게임입니다.\n";
	cout << "처음 key와 나중에 누른 key 사이의 시간을 10초로 만들어놓았습니다.\n";
	cout << "============================================================\n";
	cout << "아무키나 누르세요.\n";
	cout << "============================================================\n";
}

int main()
{
	gameInit();

	bool started = false;
	long long start = time(NULL);

	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			cout << "!!!!!시작!!!!!\n";
			cout << "10초 후에 맞춰 아무 키나 입력해주세요.\n";
			break;
		}
	}

	//cin.ignore();

	while (true)
	{
		if (_kbhit())
		{
			cout << "!!!!!끝!!!!!\n";
			break;
		}
	}

	long long end = time(NULL);

	if (end - start > 10)
		cout << "당신이 졌습니다.\n시간이 지났습니다.\n";
	else if (end - start < 10)
		cout << "당신이 졌습니다.\n시간이 지나지 않았습니다.\n";
	else
		cout << "성공!!\n";

	cout << "경과시간 : " << end - start;

	//while (true)
	//{
	//	if (_kbhit())
	//	{
	//		cout << "입력되었습니다. ";
	//		break;
	//	}

	//	//char ch = _getch();
	//	//cout << "입력한 값은 " << ch << "입니다. \n";
	//	//cout << "int로 형변환하면 " << (int)ch << "입니다. \n";

	//	//switch (ch)
	//	//{
	//	//case 'a':
	//	//case 'A':
	//	//	break;
	//	//default:
	//	//	break;
	//	//}
	//}
	return 0;
}