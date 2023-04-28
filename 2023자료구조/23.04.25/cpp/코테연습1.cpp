#include <iostream>

using namespace std;

int main()
{
	int grid[9][9], sum, average, approximation, err;

	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			cin >> grid[j][i];

	for (int i = 0; i < 9; ++i)
	{
		sum = 0;
		err = INT_MAX;

		for (int j = 0; j < 9; ++j)
			sum += grid[j][i];
	
		average = round(sum / 9.0);

		for (int j = 0; j < 9; ++j)
		{
			if (err > abs(average - grid[j][i]))
			{
				err = abs(average - grid[j][i]);
				approximation = grid[j][i];
			}
		}

		cout << average << ' ' << approximation << endl;
	}


	return 0;
}