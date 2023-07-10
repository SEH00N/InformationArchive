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

class Item {
public:
	Item() : id{ 0 }, rarity{ 0 }, owner{ 0 } {}

public:
	void Upgrade(int val) { this->rarity += val; }

public:
	int id;
	int rarity;
	int owner;
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