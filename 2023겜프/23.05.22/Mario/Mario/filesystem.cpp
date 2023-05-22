#include <iostream>
#include <fstream>
#include <string>

int main()
{
	//std::ofstream writeFile("test2.txt");
	//char arr[7] = "SEH00N";

	//if (writeFile.is_open())
	//{
	//	writeFile.write(arr, sizeof(arr) / sizeof(char));
	//	writeFile << "°×ÇÁ" << std::endl;
	//	writeFile << "¸Þ·Õ";
	//}

	//writeFile.close();

	//std::ofstream writeFile("test3.txt");
	//std::string str;
	//for (int i = 0; i < 5; ++i)
	//{
	//	std::cin >> str;
	//	writeFile << str << std::endl;
	//}

	//writeFile.close();

	//std::ifstream readFile("test3.txt");
	//while (readFile.eof() == false)
	//{
	//	std::cout << readFile.get() << std::endl;
	//}

	//std::ifstream readFile("test3.txt");
	//std::string str;

	//while(getline(readFile, str))
	//	std::cout << str << std::endl;

	std::ifstream readFile("test3.txt");
	char buf[1024];
	readFile.getline(buf, 14);
	std::cout << buf << std::endl;
}