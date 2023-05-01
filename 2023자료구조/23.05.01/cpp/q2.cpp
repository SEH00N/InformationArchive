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
				cout << "��ȣ �˻� ����" << endl;
				return 0;
			}
			else //�´� ���
				st.pop();
		}
		else if (input[i] == ')')
		{
			if (st.empty() || input[i] - 1 != st.top()) //�´� ���
			{
				cout << "��ȣ �˻� ����" << endl;
				return 0;
			}
			else
				st.pop();
		}
	}

	if(st.empty())
		cout << "��ȣ �˻� ����" << endl;
	else
		cout << "��ȣ �˻� ����" << endl;

	return 0;
}