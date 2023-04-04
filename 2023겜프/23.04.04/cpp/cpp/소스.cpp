#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

//enum class Syllable {
//	DO = 0,
//	RE,
//	MI,
//	FA,
//	SOL,
//	LA,
//	TI,
//	HIGHT_DO,
//};

void Init();
void Ready();
int PlaySyllable(const float* frequencies, const string* syllables, int size); \
bool GetAnswer(int answer);

int main()
{
	srand((unsigned int)time(NULL));

	float frequencies[] = { 523.25f, 587.33f, 659.26f, 698.46f, 783.99f, 880, 987.77f, 1046.5f };
	string syllables[] = { "��", "��", "��", "��", "��", "��", "��", "��" };

	while (true)
	{
		Init();
		Ready();

		int answer = PlaySyllable(frequencies, syllables, sizeof(frequencies) / sizeof(float));

		cout << (GetAnswer(answer) ? "\n���ϼ̽��ϴ�.\n" : "\n��!\n");
		cout << "���� : " << syllables[answer] << '\n';
		cout << "������ �׸��ѱ��? ( Y / N )\n";

		char isStop = _getch();
		if (isStop == 'y')
			break;
		else
			continue;
	}

	return 0;
}

void Init()
{
	system("cls");
	cout << "------------------\n";
	cout << "| ���� ���� ���� |\n";
	cout << "-------------------------------------\n";
	cout << "���� : ó���� 8���踦 ����ְ� \n������ 8�� �� �� ���� ���� ����ش�. \n�׸��� �� ���� ��ȣ�� ������. \n";
	cout << "-------------------------------------\n";
}

void Ready()
{
	cout << "�غ��ϰ� �ƹ� Ű�� ������.\n";
	cout << "-------------------------------------\n";

	char a = _getch();
}

int PlaySyllable(const float* frequencies, const string* syllables, int size)
{
	for (int i = 0; i < size; ++i)
	{
		Sleep(0.5f * 1000);
		cout << syllables[i] << "(" << i + 1 << ") ";
		Beep(frequencies[i], 0.5f * 1000);
	}
	cout << "\n-------------------------------------\n";

	//HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_SCREEN_BUFFER_INFO cbsi;
	//GetConsoleScreenBufferInfo(h, &cbsi);
	//for (int i = 0; i < 3; ++i)
	//{
	//	SetConsoleCursorPosition(h, cbsi.dwCursorPosition);
	//	Sleep(1 * 1000);
	//	cout << 3 - i << "...";
	//}

	for (int i = 0; i < 3; ++i)
	{
		Sleep(1 * 1000);
		cout << '\r' << 3 - i << "...";
	}

	Sleep(1 * 1000);
	system("cls");

	int answer = rand() % size;
	Beep(frequencies[answer], 0.5f * 1000);

	return answer;
}

bool GetAnswer(int answer)
{
	cout << "������?";
	int input = _getch() - '0' - 1;

	return (answer == input);
}
