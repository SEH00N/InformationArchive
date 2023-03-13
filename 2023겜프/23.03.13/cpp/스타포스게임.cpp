#include <iostream>

using namespace std;

int main()
{
	cout << "------------------\n";
	cout << "스타포스 강화 게임\n";
	cout << "------------------\n";

	int iInput, iUpgrade = 0;

	cout << "현재 무기는 몇성인가요? : ";
	cin >> iUpgrade;

	srand((unsigned int)time(NULL));
	float fPercent = (float)(rand() % 10001) * 0.01f;
	cout << fPercent;

	cout << "현재 무기 Upgrade: " << iUpgrade << "성\n";
	cout << "강화 확률 Percent: " << fPercent << "%\n";
	cout << "강화하시겠습니까? 예 : 1, 아니오 : 0\n";

	cin >> iInput;
	
	if (iInput == 0)
		return 0;

	if (iUpgrade <= 2)
		if (fPercent <= 90.f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";
	else if(iUpgrade <= 5)
		if (fPercent <= 50.f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";
	else if (iUpgrade <= 9)
		if (fPercent <= 10.f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";
	else if (iUpgrade <= 10)
		if (fPercent <= 1.f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";

	return 0;
}