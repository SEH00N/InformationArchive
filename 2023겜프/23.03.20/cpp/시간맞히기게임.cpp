#include <iostream>
#include <conio.h>

using namespace std;

void gameInit()
{
	cout << "=================\n";
	cout << "| �ð���������� |\n";
	cout << "=================\n";
	cout << "============================================================\n";
	cout << "���� : �ð��� ��� �����Դϴ�.\n";
	cout << "ó�� key�� ���߿� ���� key ������ �ð��� 10�ʷ� �������ҽ��ϴ�.\n";
	cout << "============================================================\n";
	cout << "�ƹ�Ű�� ��������.\n";
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
			cout << "!!!!!����!!!!!\n";
			cout << "10�� �Ŀ� ���� �ƹ� Ű�� �Է����ּ���.\n";
			break;
		}
	}

	//cin.ignore();

	while (true)
	{
		if (_kbhit())
		{
			cout << "!!!!!��!!!!!\n";
			break;
		}
	}

	long long end = time(NULL);

	if (end - start > 10)
		cout << "����� �����ϴ�.\n�ð��� �������ϴ�.\n";
	else if (end - start < 10)
		cout << "����� �����ϴ�.\n�ð��� ������ �ʾҽ��ϴ�.\n";
	else
		cout << "����!!\n";

	cout << "����ð� : " << end - start;

	//while (true)
	//{
	//	if (_kbhit())
	//	{
	//		cout << "�ԷµǾ����ϴ�. ";
	//		break;
	//	}

	//	//char ch = _getch();
	//	//cout << "�Է��� ���� " << ch << "�Դϴ�. \n";
	//	//cout << "int�� ����ȯ�ϸ� " << (int)ch << "�Դϴ�. \n";

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