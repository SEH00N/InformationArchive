#include <iostream>

class Item {
public:
	Item() : id{ 0 }, rarity{ 0 }, owner{ 0 } {}

public:
	void Test() {
		std::cout << "ItemÀÇ Test\n";
	}

public:
	int id;
	int rarity;
	int owner;
};

typedef void (Item::*TEST_FUNC)();

int main()
{
	TEST_FUNC testfn;
	Item item;

	testfn = &Item::Test;

	Item i1;
	(i1.*testfn)();

	Item* i2 = new Item();
	(*(i2).*testfn)();
	(i2->*testfn)();

	return 0;
}