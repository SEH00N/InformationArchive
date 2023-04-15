#include <iostream>
#include <string>

using namespace std;

template<class T>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

int main()
{
	string str1, str2;
	int i1, i2;
	double d1, d2;
	cout << "띄어쓰기를 기준으로 문자열 2개를 입력하시오 : ";
	cin >> str1 >> str2;
	cout << "띄어쓰기를 기준으로 실수 2개를 입력하시오 : ";
	cin >> d1 >> d2;
	cout << "띄어쓰기를 기준으로 정수 2개를 입력하시오 : ";
	cin >> i1 >> i2;
	
	::swap<string>(str1, str2);
	::swap<int>(i1, i2);
	::swap<double>(d1, d2);

	cout << "swap() 함수 호출 후 결과입니다." << endl;

	cout << str1 << ' ' << str2 << endl;
	cout << d1 << ' ' << d2 << endl;
	cout << i1 << ' ' << i2 << endl;

	return 0;
}