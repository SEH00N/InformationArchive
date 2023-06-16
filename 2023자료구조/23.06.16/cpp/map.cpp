#include <map>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int count, answer = 0;
	char last;
	std::string word;
	std::unordered_map<char, bool> comparer;

	std::cin >> count;


	for (int i = 0; i < count; ++i)
	{
		std::cin >> word;
		last = ' ';

		for (int j = 0; j < word.size(); ++j)
		{
			if (last == word[j])
				continue;

			last = word[j];
			if (comparer.find(word[j]) == comparer.end())
				comparer.insert(std::make_pair(word[j], true));
			else if (comparer[word[j]])
			{
				comparer.clear();
				break;
			}
		}

		if (comparer.size() > 0)
			++answer;
	}

	std::cout << answer;

	return 0;
}

//int main()
//{
//	std::map<std::string, int> map;
//	int unlisten, unwatch;
//	std::string name;
//	std::cin >> unlisten >> unwatch;
//
//	for (int i = 0; i < unlisten; ++i)
//	{
//		std::cin >> name;
//		if (map.find(name) == map.end())
//			map.insert(std::make_pair(name, 0));
//	}
//
//	for (int i = 0; i < unwatch; ++i)
//	{
//		std::cin >> name;
//		if (map.find(name) != map.end())
//			map[name]++;
//	}
//
//	std::vector<std::string> answer;
//	for (auto iter = map.begin(); iter != map.end(); iter++)
//		if (iter->second == 1)
//			answer.push_back(iter->first);
//
//	std::cout << answer.size() << '\n';
//	for (auto iter = answer.begin(); iter != answer.end(); iter++)
//		std::cout << *iter << '\n';
//
//	return 0;
//}

//int main()
//{
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(NULL);
//	std::cout.tie(NULL);
//
//	int count, question;
//	std::unordered_map<std::string, int> dictionary;
//	std::vector <std::string> dictionary2;
//	std::string pokemon;
//	std::cin >> count >> question;
//
//	for (int i = 0; i < count; ++i)
//	{
//		std::cin >> pokemon;
//		dictionary.insert(std::make_pair(pokemon, i + 1));
//		dictionary2.push_back(pokemon);
//	}
//
//	for (int i = 0; i < question; ++i)
//	{
//		std::cin >> pokemon;
//
//		if (dictionary.find(pokemon) != dictionary.end())
//			std::cout << dictionary[pokemon] << '\n';
//		else
//			std::cout << dictionary2[std::stoi(pokemon) - 1] << '\n';
//	}
//
//	return 0;
//}

//int main()
//{
//	int count;
//	std::map<std::string, int> books;
//	std::string book;
//	std::cin >> count;
//
//	for (int i = 0; i < count; ++i)
//	{
//		std::cin >> book;
//		if (books.find(book) != books.end())
//			books[book]++;
//		else
//			books.insert(std::make_pair(book, 1));
//	}
//
//	count = -1;
//	for (auto iter = books.begin(); iter != books.end(); iter++)
//	{
//		if (iter->second > count)
//		{
//			book = iter->first;
//			count = iter->second;
//		}
//	}
//
//	std::cout << book;
//
//	return 0;
//}