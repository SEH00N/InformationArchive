#include <iostream>

using namespace std;

int main()
{
	cout << "------------------\n";
	cout << "��Ÿ���� ��ȭ ����\n";
	cout << "------------------\n";

	int iInput, iUpgrade = 0;

	cout << "���� ����� ��ΰ���? : ";
	cin >> iUpgrade;

	srand((unsigned int)time(NULL));
	float fPercent = (float)(rand() % 10001) * 0.01f;
	cout << fPercent;

	cout << "���� ���� Upgrade: " << iUpgrade << "��\n";
	cout << "��ȭ Ȯ�� Percent: " << fPercent << "%\n";
	cout << "��ȭ�Ͻðڽ��ϱ�? �� : 1, �ƴϿ� : 0\n";

	cin >> iInput;
	
	if (iInput == 0)
		return 0;

	if (iUpgrade <= 2)
		if (fPercent <= 90.f)
			cout << "��ȭ ����\n";
		else
			cout << "��ȭ ����\n";
	else if(iUpgrade <= 5)
		if (fPercent <= 50.f)
			cout << "��ȭ ����\n";
		else
			cout << "��ȭ ����\n";
	else if (iUpgrade <= 9)
		if (fPercent <= 10.f)
			cout << "��ȭ ����\n";
		else
			cout << "��ȭ ����\n";
	else if (iUpgrade <= 10)
		if (fPercent <= 1.f)
			cout << "��ȭ ����\n";
		else
			cout << "��ȭ ����\n";

	return 0;
}