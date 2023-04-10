#include <iostream>

using namespace std;

class Test {
public :
	static int I;
	void print() { cout << I << '\n'; }
};

class Complex {
	friend Complex add(Complex&, Complex&);

private:
	double real;
	double imag;
public:
	Complex(double r = 0.0, double i = 0.0) : real{ r }, imag{ i } {}
	void print() { cout << real << " + " << imag << " i \n"; }
};

Complex add(Complex& c1, Complex& c2) {
	Complex c{ c1.real + c2.real, c1.imag + c2.imag };
	return c;
}

int main()
{
	Test t;
	t.print();

	Complex c1{ 1, 2 }, c2{ 3, 4 };
	Complex c3 = add(c1, c2);

	c3.print();

	return 0;
}

int Test::I = 0;