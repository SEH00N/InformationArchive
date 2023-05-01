#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	string input;
	stack<char> st;

	getline(cin, input);

	for (int i = 0; i < input.length(); ++i)
	{
		if (input[i] == '{' || input[i] == '(' || input[i] == '[')
		{
			st.push(input[i]);
		}
		else if (input[i] == '}' || input[i] == ']')
		{
			if (st.empty() || input[i] - 2 != st.top())
			{
				cout << "괄호 검사 실패" << endl;
				return 0;
			}
			else //맞는 경우
				st.pop();
		}
		else if (input[i] == ')')
		{
			if (st.empty() || input[i] - 1 != st.top()) //맞는 경우
			{
				cout << "괄호 검사 실패" << endl;
				return 0;
			}
			else
				st.pop();
		}
	}

	if(st.empty())
		cout << "괄호 검사 성공" << endl;
	else
		cout << "괄호 검사 실패" << endl;

	return 0;
}