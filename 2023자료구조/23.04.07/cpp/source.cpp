#include <iostream>

using namespace std;

class Box {
private:
	double length;
	double width;
	double height;

public:
	Box(double l = 0, double w = 0, double h = 0) : length{ l }, width{ w }, height{ h } {}

	double getVolume() {
		return length * width * height;
	}

	Box operator+(const Box& box) {
		Box result{this->length + box.length, this->width + box.length, this->height + box.height};
		return result;
	}

	bool operator==(Box& box) {
		//return ((this->length == box.length) && (this->width == box.width) && (this->height == box.height));
		return (this->getVolume() == box.getVolume());
	}

	bool operator<(Box& box) {
		//return ((this->length < box.length) && (this->width < box.width) && (this->height < box.height));
		return (this->getVolume() < box.getVolume());
	}

	bool operator>(Box& box) {
		//return ((this->length > box.length) && (this->width > box.width) && (this->height > box.height));
		return (this->getVolume() > box.getVolume());
	}
};

int main()
{
	Box a{ 1, 1, 1 }, b{ 2, 2, 2 }, c;
	c = a + b;

	cout << c.getVolume() << '\n';

	cout << (a == b ? "true\n" : "false\n");

	cout << (a < b ? "true\n" : "false\n");
	cout << (a > b ? "true\n" : "false\n");

	return 0;
}