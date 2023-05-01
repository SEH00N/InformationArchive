#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	stack<int> st;
	string input;
	int cnt = 0;
	getline(cin, input);

	for (int i = 0; i < input.length(); ++i)
	{
		if (input[i] == '(')
		{
			++cnt;
			st.push(cnt);
			cout << cnt;
		}
		else
		{
			cout << st.top();
			st.pop();
		}
	}

	return 0;
}