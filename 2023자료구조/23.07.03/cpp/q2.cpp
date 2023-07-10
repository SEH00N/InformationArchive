#include <iostream>

int main()
{
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	std::ios_base::sync_with_stdio();

	std::string str, bomb;
	std::cin >> str >> bomb;

	int bombLen = bomb.length();

	while (true)
	{
		int pos = str.find(bomb);
		if (pos > str.length())
			break;
	
		str.replace(pos, bombLen, "");
	}

	std::cout << ((str.length() > 0) ? str : "FRULA");

	return 0;
}