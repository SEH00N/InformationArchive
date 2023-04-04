#include <iostream>
#include <string>

using namespace std;

class Pizza
{
private:
	int radius;

public:
	Pizza(int radius) : radius{ radius } {}
	~Pizza() {}

	void setRadius(int radius) { this->radius = radius; }

	void print() { cout << "PIZZA (" << radius << ")\n"; }
};

class Complex
{
public:
	double real, imag;
	void print() { cout << real << " + " << imag << "i\n"; }
	Complex(double real = 0, double imag = 0) : real{ real }, imag{ imag } {}
};

class MyArray
{
public:
	int size;
	int* data;

	MyArray(int size)
	{
		this->size = size;
		data = new int[size];
	}

	~MyArray() { if (data != NULL) delete[] data; }
};

void upgrade(Pizza* pizza)  { (*pizza).setRadius(20); }

void upgrade(Pizza& pizza) { pizza.setRadius(30); }

Complex add(const Complex& c1, const Complex& c2) { return Complex(c1.real + c2.real, c1.imag + c2.imag); }

int main()
{
	Pizza pizza(19);

	upgrade(&pizza);
	pizza.print();

	upgrade(pizza);
	pizza.print();

	cout << '\n';

	Complex c1{ 1, 2 }, c2 { 3, 4 };
	Complex t;
	t = add(c1, c2);
	t.print();

	cout << '\n';

	MyArray buffer(10);
	buffer.data[0] = 1;
		MyArray clone = buffer;

	buffer.data[0] = 2;

	return 0;
}