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
	cout << "1번 문제 : 1번\n";
	cout << "2번 문제 : 3번\n";
	cout << "3번 문제 : 매개변수, 반환, 같은 종류의 객체로 초기화하는 경우\n";
	cout << "4번 문제 : MyClass(MyClass& target) : x{ target.x }, c{ target.c }, s{ target.s } {} \n";
	cout << "5번 문제 : 포인터와 같은 경우 담고 있는 주소가 같을 경우가 생김, 다음과 같은 경우 소멸자 안에서 delete를 시킬 때 할당되어있지 않은 주소를 삭제시켜 에러가 나는 상황이 생길 수 있다.\n";	
	cout
		<< "6번 문제 : \n"
		<< "MyMyClass(MyMyClass & target) { \n"
		<< "stored = new char[strlen(target.stored) + 1];\n"
		<< "strcpy_s(stored, strlen(target.stored) + 1, target.stored);\n"
		<< "}";

	return 0;
}