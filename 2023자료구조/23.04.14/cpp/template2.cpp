#include <iostream>

using namespace std;

template<class T>
class Circle {
private:
	T x, y, radius;
public:
	static const double PI;

	Circle<T>(T x, T y, T radius) : x{ x }, y{ y }, radius{ radius } {};

	double getArea() { return PI * pow(radius, 2); }
};

template<class T>
const double Circle<T>::PI = 3.141592;

int main()
{
	Circle<int> c1{ 1, 1, 5 };	
	Circle<double> c2{ 1.5, 1.5, 5.0 };

	cout << c1.getArea() << endl;
	cout << c2.getArea() << endl;

	return 0;
}