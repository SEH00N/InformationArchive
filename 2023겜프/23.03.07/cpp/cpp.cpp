#include <iostream>

using namespace std;

int main()
{
	int iNansu;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		//iNansu = rand();
		//iNansu = rand() % 52;
		iNansu = rand() % 21 + 10; //10 ~ 30 -> 0 ~ 20 + 10

		cout << iNansu << endl;
	}

	return 0;
}