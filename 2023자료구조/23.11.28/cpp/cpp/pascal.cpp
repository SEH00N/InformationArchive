#include <iostream>
#include <vector>

std::vector<std::vector<long long>> grid;

long long pascal(int row, int col)
{
	if (col == 0 || row == col)
		return 1;
	if (grid[row][col] == 0)
		grid[row][col] = pascal(row - 1, col) + pascal(row - 1, col - 1);
	return grid[row][col];
}
	
int main()
{
	int row, col;
	std::cin >> row >> col;
	grid.resize(row + 1, std::vector<long long>(row + 1));

	std::cout << pascal(row - 1,col - 1);

	return 0;
}