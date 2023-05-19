#include <iostream>
#include <stack>

//bool solution(std::string s)
//{
//	bool answer = true;
//	int temp = 0;
//
//	for (auto x : s)
//	{
//		if (x == '(')
//			temp++;
//		else
//			if (temp <= 0)
//				return false;
//			else
//				temp--;
//	}
//
//	answer = temp == 0;
//
//	return answer;
//}

//int main()
//{
//	int count, answer = 0;
//	std::string str;
//	std::cin >> count;
//
//	for (int i = 0; i < count; ++i)
//	{
//		std::stack<int> st;
//		std::cin >> str;
//		for (int j = 0; j < str.length(); ++j)
//		{
//			if (st.empty() || st.top() != str[j])
//				st.push(str[j]);
//			else
//				st.pop();
//		}
//
//		if(st.empty())
//			answer++;
//	}
//
//	std::cout << answer;
//
//	return 0;
//}

int main()
{
	int count, input, last = 0;
	std::stack<int> st;
	std::string answer = "";

	std::cin >> count;

	for (int i = 0; i < count; ++i)
	{
		std::cin >> input;

		st.push(input);
		answer.push_back('P');

		while (st.empty() == false && st.top() == last + 1)
		{
			last++;
			st.pop();
			answer.push_back('O');
		}
	}

	if (st.empty() == false)
		answer = "impossible";
	
	std::cout << "";

	return 0;
}