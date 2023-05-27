#include <iostream>
#include <string>
#include <deque>

int main()
{
	int cnt, temp;
	std::cin >> cnt;

	bool front = true, err = false;
	std::string command, arr;

	for (int i = 0; i < cnt; ++i)
	{
		err = false;

		std::cin >> command;
		std::cin >> temp;
		std::cin >> arr;

		std::deque<int> deq;
		int num = 0;

		for (int j = 0; j < arr.size(); ++j)
		{
			if ('0' <= arr[j] && arr[j] <= '9')
				num += arr[j] - '0';
			else if (temp != 0 && (arr[j] == ']' || arr[j] == ','))
			{
				deq.push_back(num);
				num = 0;
			}
		}

		for (int j = 0; j < command.size(); ++j)
		{
			if (command[j] == 'R')
				front = !front;
			else if (command[j] == 'D')
			{
				if (deq.empty())
				{
					std::cout << "error" << std::endl;
					err = true;
					break;
				}
				else
					front ? deq.pop_front() : deq.pop_back();
			}
		}

		if (err == false)
		{
			command = '[';
			while (deq.empty() == false)
			{
				command.append(std::to_string(front ? deq.front() : deq.back()));
				front ? deq.pop_front() : deq.pop_back();

				command.push_back(',');
			}

			command.pop_back();
			command.push_back(']');

			std::cout << command << std::endl;
		}
	}
}