#include <iostream>
#include <stack>

using namespace std;

class Stack
{
public:
	const static int SIZE = 10;

	Stack(char ch = ' ') : name{ ch }, top{ -1 } { cout << "Constructing Stack " << name << endl; }
	void push(char ch) {
		if (top + 1 >= SIZE) {
			cout << "Stack is Full" << endl;
			return;
		}

		stackArr[++top] = ch;
	}

	char pop() {
		if (top <= -1) {
			cout << "Stack " << name << " is Empty" << endl;
			return 0;
		}

		return stackArr[top--];
	}

private:
	char name;
	int top;
	char stackArr[SIZE];
};

int main()
{
	//Stack stack('A');
	//
	//for (int i = 0; i < 10; ++i)
	//	stack.push(i + 'A');

	//for (int i = 0; i < 10; ++i)
	//	cout << stack.pop() << ' ';

	stack<char> st1;

	st1.push('L');
	st1.push('O');
	st1.push('V');
	st1.push('E');

	for (int i = 0; i < 4; ++i) {
		cout << st1.top();
		st1.pop();
	}

	cout << endl << endl;

	stack<int> st2;
	int num;

	cout << "10진수 값을 입력하세요 : ";
	cin >> num;

	try {
		if (num < 0)
			throw num;

		while (num > 1) {
			st2.push(num % 2);
			num *= 0.5f;
		}
		st2.push(num);

		while(st2.empty() == false) {
			cout << st2.top();
			st2.pop();
		}
	} catch (int err){
		cout << "음수 " << err << "을 입력하셨습니다. 양수로 입력하세요.";
	}

	cout << endl << endl;

	stack<char> st3;
	int input, cnt = -1;

	cin >> input;

	while (input != 0) {
		++cnt;
		if (cnt % 3 == 0 && cnt != 0)
			st3.push(',');

		st3.push((input % 10) + '0');
		input *= 0.1f;
	}

	while (st3.empty() == false) {
		cout << st3.top();
		st3.pop();
	}

	return 0;
}