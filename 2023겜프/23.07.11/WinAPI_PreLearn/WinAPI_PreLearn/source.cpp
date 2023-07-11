#include <iostream>
#include <functional>

typedef struct _pos {
	int x;
	int y;
}POS, *PPOS;

typedef int INT;
typedef int* INTPTR;

//typedef int Add(int a, int b);

typedef int (FUNC_TYPE)(int, int);
// ==
// using FUNC_TYPE = int(int, int); // <- modern c++

int Add(int a, int b) { return a + b; }
int Sub(int a, int b) { return a - b; }

class Item {
public:
	Item() : id{ 0 }, rarity{ 0 }, owner{ 0 } {}
public:
	int id;
	int rarity;
	int owner;
};

bool IsRarityItem(Item* item, int rarity) { return item->rarity >= rarity; }
bool IsIdItem(Item* item, int id) { return item->id == id; }
typedef bool (COMPARER)(Item* item, int value);

//Item* FindItem(Item items[], int count, COMPARER* comparer)
Item* FindItem(Item items[], int count, std::function<bool(Item* item, int val)> comparer = IsIdItem)
{
	for (int i = 0; i < count; ++i)
	{
		Item* item = &items[i];
		if (comparer(item, 3))
			return item;
	}

	return nullptr;
}

int main()
{
	Item items[10] = {};
	items[2].id = 3;
	items[2].rarity = 3;

	Item* selectedItem = FindItem(items, 10, IsRarityItem);
	
	std::cout << selectedItem->id << std::endl;
}

//int main()
//{
//	int a;
//	float b;
//
//	FUNC_TYPE* fn;
//	fn = Add;
//	
//	int val = fn(1, 2);
//	int val2 = (*fn)(1, 2);
//
//	std::cout << Add << std::endl;
//	std::cout << val << std::endl;
//	std::cout << val2 << std::endl;
//
//	//INT a = 10;
//	//INTPTR ptr = &a;
//	//*ptr = 5;
//
//	//std::cout << a;
//
//	return 0;
//}