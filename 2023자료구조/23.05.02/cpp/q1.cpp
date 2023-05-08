#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
	map<char, int> order;
	stack<char> st;
	string infix;
	getline(cin, infix);

	order.insert({ '(', 0 });
	order.insert({ '-', 1 });
	order.insert({ '+', 1 });
	order.insert({ '*', 2 });
	order.insert({ '/', 2 });

	for (int i = 0; i < infix.length(); ++i)
	{
		if (infix[i] == ')')
		{
			while (st.top() != '(')
			{
				cout << st.top();
				st.pop();
			}

			st.pop();
		}
		else if (infix[i] == '(')
			st.push(infix[i]);
		else if (order.count(infix[i]))
		{
			if (st.empty() || order[infix[i]] > order[st.top()])
				st.push(infix[i]);
			else
			{
				cout << st.top();
				st.pop();
			}
		}
		else
			cout << infix[i];
	}

	while (st.empty() == false)
	{
		cout << st.top();
		st.pop();
	}

	return 0;
}