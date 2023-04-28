#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int num, cnt = 0;
	cin >> num;

	for (int i = num / 2; i > 0; --i)
	{
		int temp = i;
		vector<int> vec;
		while (true)
		{
			int sum = 0;
			vec.push_back(temp++);
			
			for (int x : vec)
				sum += x;

			if (sum < num)
			{
				continue;
			}
			else if (sum == num)
			{
				cout << vec[0];
				for (int j = 1; j < vec.size(); j++)
					cout << " + " << vec[j];

				cout << " = " << num << endl;

				++cnt;
			}
			else
				break;
		}
	}

	cout << cnt;

	return 0;
}