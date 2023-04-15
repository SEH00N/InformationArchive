#include <iostream>

using namespace std;

int dividePizza(int slices, int person)
{
	if (person <= 0)
		throw person;
	if (slices < 0)
		throw slices;

	cout << "�ѻ���� ���ڴ� " << slices / person << "�Դϴ�." << endl;
}

int main()
{
	int pizza_slices = 0;
	int persons = -1;

	cout << "���� �������� �Է��Ͻÿ� : ";
	cin >> pizza_slices;

	cout << "������� �Է��Ͻÿ� : ";
	cin >> persons;

	try {
		dividePizza(pizza_slices, persons);
	}
	catch (int e) {
		cout << "�߸��� �Է��Դϴ�." << endl;
	}


	return 0;
}