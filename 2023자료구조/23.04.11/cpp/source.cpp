#include <iostream>

using namespace std;

class Box {
private:
	double length;
	double width;
	double height;
public:
	static int count;

	friend Box operator+(Box proto, Box other);
	friend bool operator==(Box proto, Box other);
	friend bool operator<(Box proto, Box other);

	Box(double length, double width, double height) : length{ length }, width{ width }, height{ height } { ++count; }
	double volume() { return length * width * height; }
};

int Box::count = 0;

Box operator+(Box proto, Box other) { return { proto.length + other.length, proto.width + other.width, proto.height + other.height }; }
bool operator==(Box proto, Box other) { return { proto.volume() == other.volume() }; }
bool operator<(Box proto, Box other) { return { proto.volume() < other.volume() }; }

int main()
{
	Box box1{ 1, 2, 3 };
	Box box2{ 1, 2, 5 };
	Box box3 = box1 + box2;

	cout << "box3.volume : " << box3.volume() << endl;
	cout << "box1 == box2 : " << (box1 == box2 ? "true" : "false") << endl;
	cout << "box1 < box2 : " << (box1 < box2 ? "true" : "false") << endl;
	cout << "ÀüÃ¼ °´Ã¼ ¼ö : " << Box::count << endl;

	return 0;
}