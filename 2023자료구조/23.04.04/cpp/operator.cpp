#include <iostream>
#include <string>

using namespace std;

class Box {
private:
	double length, width, height;
public:
	Box(double length, double width, double height) : length{ length }, width{ width }, height{ height } {}
	Box() : length{ 0 }, width{ 0 }, height{ 0 } {}
	void Display() {
		cout << '(' << length << ", " << width << ", " << height << ")\n";
	}
};

class MyVector {
private:
	double x, y;
public :
	MyVector(double x = 0.0, double y = 0.0) : x{ x }, y{ y } {}
	string toString() {
		return "(" + to_string(x) + ", " + to_string(y) + ")";
	}

	MyVector operator+(const MyVector& v2) {
		MyVector v;
		v.x = this->x + v2.x;
		v.y = this->y + v2.y;

		return v;
	}
};

class Counter {
private:
	int value;

public:
	Counter() : value{ 0 } {};

	int getValue() const {
		return value;
	}

	void setValue(int x) {
		value = x;
	}

	Counter& operator++() {
		this->value += 1;

		return *this;
	};
};

class Time {
private:
	int hour, min, sec;

public:
	Time(int hour = 0, int min = 0, int sec = 0) : hour{ hour }, min{ min }, sec{ sec } {}

	void Print() {
		cout << hour << " : " << min << " : " << sec << '\n';
	}

	bool operator== (Time& t2) {
		return ((t2.hour == this->hour) && (t2.min == this->min) && (t2.sec == this->sec));
	}

	bool operator!= (Time& t2) {
		return !(*this == t2);
	}
};

int main()
{
	MyVector v1{ 0, 5 }, v2{ 5, 0 };
	cout << "v1 => " << v1.toString() << '\n';
	cout << "v2 => " << v2.toString() << '\n';
	cout << "v1 + v2 => " << (v1 + v2).toString() << '\n';

	Counter c;
	cout << c.getValue() << '\n';
	
	++c;
	cout << c.getValue() << '\n';

	Time t1{ 10, 32, 12 }, t2{ 11, 32, 12 };
	cout << "t1 => ";
	t1.Print();

	cout << "t2 => ";
	t2.Print();

	cout << "t1 == t2 : " << (t1 == t2 ? "true" : "false") << '\n';
	cout << "t1 != t2 : " << (t1 != t2 ? "true" : "false") << '\n';

	
	return 0;
}