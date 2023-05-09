#include <iostream>

using namespace std;

class Queue {
private:
	int* buf;
	int qsize;
	int front;
	int rear;

public:
	void InitQueue(int size) {
		qsize = size;
		buf = new int[qsize];
		front = -1;
		rear = -1;
	}

	void Enqueue(int item) {
		if (Full())
			return;

		buf[rear++] = item;
	}

	int Dequeue() {
		if (Empty())
			return -1;

		return buf[++front];
	}

	bool Empty() {
		return (front == rear);
	}

	bool Full() {
		return (rear == qsize - 1);
	}
};

int main()
{
	int i;
	Queue q1;
	
	q1.InitQueue(10);
	for (int i = 1; i <= 11; ++i) {
		cout << i << " 입력 \n";
		q1.Enqueue(i);
	}

	cout << endl;

	while (q1.Empty() == false) {
		cout << q1.Dequeue() << " 출력 \n";
	}

	cout << endl;

	return 0;
}