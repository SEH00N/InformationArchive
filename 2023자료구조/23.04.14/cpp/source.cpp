#include <iostream>

using namespace std;

int dividePizza(int slices, int person)
{
	if (person <= 0)
		throw person;
	if (slices < 0)
		throw slices;

	cout << "한사람당 피자는 " << slices / person << "입니다." << endl;
}

int main()
{
	int pizza_slices = 0;
	int persons = -1;

	cout << "피자 조각수를 입력하시오 : ";
	cin >> pizza_slices;

	cout << "사람수를 입력하시오 : ";
	cin >> persons;

	try {
		dividePizza(pizza_slices, persons);
	}
	catch (int e) {
		cout << "잘못된 입력입니다." << endl;
	}


	return 0;
}