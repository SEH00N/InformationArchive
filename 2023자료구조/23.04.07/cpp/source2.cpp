#include <iostream>

using namespace std;

class Counter {
private:
	int value;

public:
	Counter() : value{ 0 } {}
	~Counter() {}

	int getValue() const { return value; }
	void setValue(int x) { value = x; }

	Counter& operator++() {
		++value;
		return *this;
	}
	Counter& operator++(int) {
		value++;
		return *this;
	}
};

int main()
{
	Counter c;
	cout << ((c++).getValue()) << '\n';
	cout << ((++c).getValue()) << '\n';

	return 0;
}