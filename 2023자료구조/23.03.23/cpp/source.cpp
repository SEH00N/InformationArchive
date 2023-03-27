#include <iostream>
#include <string>

using namespace std;

class Pizza
{
private:
	int radius;

public :
	Pizza(int radius) : radius{ radius } {}

	void setRadius(int radius) {
		this->radius = radius;
	}

	int getRadius() {
		return radius;
	}
};

class Book
{
private:
	string title;
	int cost;
public:
	Book(string title, int cost) : title{ title }, cost{ cost } {}
	inline void print()
	{
		cout << "제목 : " << title << ",\t가격 : " << cost << '\n';
	}
};

class Character
{
private:
	int x, y, hp;

public:
	Character(int x, int y, int hp) :x{ x }, y{ y }, hp{ hp } {}
	void setX(int x)
	{
		this -> x = x;
	}

	void setY(int y)
	{
		this->y = y;
	}

	inline void print()
	{
		cout << "x : " << x << "\ty : " << y << "\tHP : " << hp << '\n';
	}
};

void makeDouble(Pizza& pizza)
{
	pizza.setRadius(pizza.getRadius() * 2);
}

int main()
{
	//Pizza pizza(10);
	//makeDouble(pizza);
	//cout << pizza.getRadius() << "인치 피자\n";

	//Book books[2] = {
	//	Book("어서와 C++", 25000),
	//	Book("어서와 C", 22000)
	//};
	//cout << "소장하고 있는 책 정보\n";
	//cout << "====================================\n";
	//for (Book& b : books)
	//	b.print();
	//cout << "====================================\n";

	//cout << "캐릭터 #1\n";
	//Character character(0, 0, 100);
	//for (int i = 0; i < 100; i += 10)
	//{
	//	character.setX(i);
	//	character.print();
	//}

	return 0;
}