#include <iostream>
#include <Windows.h>
#include "console.h"

using namespace std;

int main()
{
	cout << "�߻���� ���μ�\n";
	
	Go2xy(10, 10);
	ConsoleCursor(false, 1);

	Sleep(1000);

	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);

	cout << "��������\n";

	int a;
	cin >> a;

	return 0;
}