#include <iostream>
#include <string>

using namespace std;

int arr[100]{0, 1, 1};

int fibo(int n)
{
	if (arr[n] != 0)
		return arr[n];

	arr[n] = fibo(n - 1) + fibo(n - 2);

	return arr[n];
}

int main()
{
	//int num = 0;
	//cin >> num;

	//cout << fibo(num);

	//string str;
	//int i;

	//getline(cin, str);
	//cin >> i;

	//cout << str[i - 1];

	//string str;
	//int loopCnt;
	//cin >> loopCnt;

	//cin.ignore();

	//for (int i = 0; i < loopCnt; i++)
	//{
	//	getline(cin, str);
	//	cout << str[0] << str[str.length() - 1] << '\n';
	//}

	//char temp;
	//cin >> temp;
	//cout << (int)temp;

	//int cnt, answer = 0;
	//string input;
	//cin >> cnt >> input;

	//for (int i = 0; i < cnt; i++)
	//	answer += input[i] - 48;

	//cout << answer;

	//int alphabets[26] = { -1, };
	//string str;
	//cin >> str;

	//for (int i = 0; i < 26; i++)
	//	alphabets[i] = -1;

	//for (int i = 0; i < str.length(); i++)
	//	if(alphabets[str[i] - 97] == -1)
	//		alphabets[str[i] - 97] = i;

	//for (int i = 0; i < 26; i++)
	//	cout << alphabets[i] << ' ';

	//int inputCnt, loopCnt;
	//string str;
	//cin >> inputCnt;

	//for (int i = 0; i < inputCnt; i++)
	//{
	//	cin >> loopCnt >> str;
	//	for (int j = 0; j < str.length(); j++)
	//		for (int k = 0; k < loopCnt; k++)
	//			cout << str[j];
	//	cout << '\n';
	//}

	int cnt = 0;
	string str;
	
	while (true) {
		getline(cin, str);

		if (str.length() == 1)
			cout << 0;
		else
		{
			for (int i = 1; i < str.length() - 1; i++)
			{
				if (str[i] == ' ')
					cnt++;
			}

			cout << cnt + 1;
		}
	}
	return 0;
}