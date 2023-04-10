#include <iostream>
#include <string>

using namespace std;

class MyClass {
private:
	int x;
	char c;
	string s;

public:
	MyClass() : x{ 0 }, c{ '\0' }, s{""} {}
	MyClass(int x, char c, string s) : x{ x }, c{ c }, s{ s } {}
	MyClass(const MyClass& target) : x{ target.x }, c{ target.c }, s{ target.s } {}
};

class MyMyClass {
private:
	char* stored;
public:
	MyMyClass(const char* str) {
		stored = new char[strlen(str) + 1];
		strcpy_s(stored, strlen(str) + 1, str);
	}
	MyMyClass(const MyMyClass& target) {
		stored = new char[strlen(target.stored) + 1];
		strcpy_s(stored, strlen(target.stored) + 1, target.stored);
	}
	~MyMyClass() {
		delete[] stored;
	}
};

int main()
{
	cout << "1�� ���� : 1��\n";
	cout << "2�� ���� : 3��\n";
	cout << "3�� ���� : �Ű�����, ��ȯ, ���� ������ ��ü�� �ʱ�ȭ�ϴ� ���\n";
	cout << "4�� ���� : MyClass(MyClass& target) : x{ target.x }, c{ target.c }, s{ target.s } {} \n";
	cout << "5�� ���� : �����Ϳ� ���� ��� ��� �ִ� �ּҰ� ���� ��찡 ����, ������ ���� ��� �Ҹ��� �ȿ��� delete�� ��ų �� �Ҵ�Ǿ����� ���� �ּҸ� �������� ������ ���� ��Ȳ�� ���� �� �ִ�.\n";	
	cout
		<< "6�� ���� : \n"
		<< "MyMyClass(MyMyClass & target) { \n"
		<< "stored = new char[strlen(target.stored) + 1];\n"
		<< "strcpy_s(stored, strlen(target.stored) + 1, target.stored);\n"
		<< "}";

	return 0;
}