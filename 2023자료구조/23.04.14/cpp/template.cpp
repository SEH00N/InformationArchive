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
	cout << "���⸦ �������� ���ڿ� 2���� �Է��Ͻÿ� : ";
	cin >> str1 >> str2;
	cout << "���⸦ �������� �Ǽ� 2���� �Է��Ͻÿ� : ";
	cin >> d1 >> d2;
	cout << "���⸦ �������� ���� 2���� �Է��Ͻÿ� : ";
	cin >> i1 >> i2;
	
	::swap<string>(str1, str2);
	::swap<int>(i1, i2);
	::swap<double>(d1, d2);

	cout << "swap() �Լ� ȣ�� �� ����Դϴ�." << endl;

	cout << str1 << ' ' << str2 << endl;
	cout << d1 << ' ' << d2 << endl;
	cout << i1 << ' ' << i2 << endl;

	return 0;
}