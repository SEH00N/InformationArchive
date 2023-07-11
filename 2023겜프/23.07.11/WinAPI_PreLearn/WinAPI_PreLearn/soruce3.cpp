#include <iostream>
#include <vector>
#include <memory>

enum class ItemType {
	None,
	Weapon,
	Armor
};

class Item {
public:
	Item(int itemId, int rarity, ItemType type) : id{ itemId }, rarity{ rarity }, type{ type } {}
	Item() : id{ 0 }, rarity{ 0 }, type{ ItemType::None } {}

public:
	auto ResetItem() {
		auto lambda = [this]() {
			id = 0;
		}

		return lambda;
	}

public:
	void Upgrade(int val) { this->rarity += val; }

public:
	int id;
	int rarity;
	ItemType type;
};

class IsWeapon {
public:
	bool operator()(Item& item) { return (item.type == ItemType::Weapon); }
};

class IDCompare {
private:
	int id;
public:
	IDCompare(int id) : id{id} {}
public:
	bool operator()(Item& item) { return (item.id == id); }
};

int main()
{
	std::vector<Item> vec;
	vec.push_back(Item(1, 1, ItemType::None));
	vec.push_back(Item(2, 10, ItemType::Weapon));
	vec.push_back(Item(3, 100, ItemType::Armor));

	auto findLambda = [](Item& item) { return (item.type == ItemType::Weapon); };

	//auto foundedItem = std::find_if(vec.begin(), vec.end(), findLambda);
	//auto foundedItem = std::find_if(vec.begin(), vec.end(), [](Item& item) { return (item.type == ItemType::Weapon); });

	//auto foundedItem = std::find_if(vec.begin(), vec.end(), IDCompare(3));
	int itemid = 3;
	int rarity = 100;
	auto foundedItem = std::find_if(vec.begin(), vec.end(), [itemid, &rarity](Item& item) { return (item.id == itemid && item.rarity == rarity); });
	
	if (foundedItem != vec.end())
		std::cout << "아이템 ID는 " << foundedItem->id << "입니다." << std::endl;

	//bool operator()(Item & item) { return (item.type == ItemType::Weapon); }

	//Item i1(1, 2, ItemType::None);
	//Item i2;

	//i2 = i1;
	//i2 = static_cast<Item&&>(i1);
	//i2 = std::move(i1);

	//std::unique_ptr<Item> uptr = std::make_unique<Item>();
	//std::unique_ptr<Item> uptr2 = std::make_unique<Item>();

	return 0;
}