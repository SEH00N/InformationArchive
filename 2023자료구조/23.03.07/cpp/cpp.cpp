#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
#pragma region 캔디
	//int currentMoney, candyCost;

	//cout << "현재 가지고 있는 돈: ";
	//cin >> currentMoney;

	//cout << "캔디의 가격: ";
	//cin >> candyCost;

	//cout << "최대로 살 수 있는 캔디의 개수 = " << currentMoney / candyCost << endl;
	//cout << "캔디 구입 후 남은 돈 = " << currentMoney % candyCost;
#pragma endregion

#pragma region 발표
	//int cnt = 0;
	//vector<string> people;

	//cout << "총 인원 수 설정 : ";
	//cin >> cnt;

	//cout << cnt << "명의 이름을 입력해주세요." << endl;

	//for (int i = 0; i < cnt; i++)
	//{
	//	string tempName;
	//	cin >> tempName;
	//	people.push_back(tempName);
	//}

	//int start;

	//cout << "1을 누르면 뽑기가 시작합니다. 종료는 0을 누르세요." << endl;
	//cin >> start;

	//if (start)
	//{
	//	cout << "뽑기를 시작합니다." << endl;

	//	srand((unsigned int)time(NULL));
	//	cout << "발표할 사람 : " << people[rand() % cnt];
	//}
	//else
	//	cout << "종료" << endl;

#pragma endregion

#pragma region 이름과 주소

	//string name, address;

	//cout << "이름을 입력해주세요 : ";
	//getline(cin, name);
	//
	//cin.ignore();
	// 
	//cout << "주소를 입력해주세요 : ";
	//getline(cin, address);

	//cout << address << "의 " << name << "씨 안녕하세요?";
	
#pragma endregion

#pragma region 도전1 문자 위치 찾기

	//string str = "When in rome, do as the Romans.";

	//cout << str.find("rome") << endl;

#pragma endregion

#pragma region 도전2 특정 문자 삭제하기

	//string id;
	//
	//cout << "주민등록번호를 입력해주세요 : ";
	//getline(cin, id);

	//id.erase(id.find('-'), 1);

	//cout << "-가 제거된 주민등록번호 : " << id;

#pragma endregion

#pragma region 도전3 해밍 거리 구하기

	//int cnt = 0;
	//string dna1, dna2;

	//cout << "DNA1 : ";
	//getline(cin, dna1);

	//cout << "DNA2 : ";
	//getline(cin, dna2);

	//for (int i = 0; i < dna1.size(); i++)
	//	if (dna1.at(i) != dna2.at(i))
	//		cnt++;

	//cout << "해밍거리 : " << cnt;

#pragma endregion

#pragma region 도전4 행맨

	srand((unsigned int)time(NULL));

	string words[] = { "junseong", "sehoon", "minsung" };
	string randomWord = words[rand() % (sizeof(words) / sizeof(string))];
	string answer;
	char input;

	for (int i = 0; i < randomWord.size(); i++)
		answer.push_back('_');

	while (answer != randomWord)
	{
		cout << '\n' << answer << "\n\n";

		cout << "글자를 입력해주세요 : ";
		cin >> input;

		size_t inputLetterPos = randomWord.find(input);
		if (inputLetterPos != string::npos)
		{
			randomWord[inputLetterPos] = '\0';
			answer[inputLetterPos] = input;
		}

		if (answer.find('_') == string::npos)
			break;
	}

	cout << '\n' << answer << '\n';
	cout << "\n정답!!";

#pragma endregion

	return 0;
}