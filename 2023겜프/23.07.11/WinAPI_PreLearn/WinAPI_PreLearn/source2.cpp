#include <iostream>

class Functor
{
public:
	void operator()(int val)
	{
		std::cout << "ÇÔ¼ö °´Ã¼" << std::endl;
		value += val;
		std::cout << value << std::endl;
	}
public:
	int value = 0;
};

enum class ItemType {
	None,
	Weapon,
	Armor
};

class Item {
public:
	Item(int itemId, int rarity, ItemType type) : id{ itemId }, rarity{ rarity }, type{ type } {}

public:
	void Upgrade(int val) { this->rarity += val; }

public:
	int id;
	int rarity;
	ItemType type;
};

void Test()
{

}

int main()
{
	Test();
	Functor fn;
	fn(10);

	return 0;
}