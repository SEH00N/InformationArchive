#include <iostream>
#include <thread>
#include <ctime>

void Add(int* val, int min, int max) {
	for (int i = min; i <= max; ++i) {
		*val += i;
	}
}

int main()
{
	int num1 = 0;

	clock_t start1 = clock();

	std::thread thread1(Add, &num1, 1, 3333);
	std::thread thread2(Add, &num1, 3334, 6666);
	std::thread thread3(Add, &num1, 6667, 10000);

	thread1.join();
	thread2.join();
	thread3.join();

	clock_t end1 = clock();
	
	std::cout << num1 << '\n';
	std::cout << (end1 - start1) << '\n';

	int num2 = 0;

	clock_t start2 = clock();

	Add(&num2, 1, 10000);

	clock_t end2 = clock();

	std::cout << num2 << '\n';
	std::cout << (end2 - start2) << '\n';
}
