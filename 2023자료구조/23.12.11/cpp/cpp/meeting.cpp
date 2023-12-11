#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int room;
	std::cin >> room;
	
	// <끝나는 시간, 시작하는 시간>
	std::vector<std::pair<int, int>> rooms = std::vector<std::pair<int, int>>(room);
	for (int i = 0; i < room; ++i)
		std::cin >> rooms[i].second >> rooms[i].first;

	std::sort(rooms.begin(), rooms.end());

	int timer = 0, answer = 0;
	for (int i = 0; i < room; ++i)
	{
		if (rooms[i].second < timer)
			continue;

		timer = rooms[i].first;
		++answer;
	}

	std::cout << answer;

	return 0;
}