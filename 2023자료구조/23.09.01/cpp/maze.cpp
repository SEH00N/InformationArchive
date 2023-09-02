#include<vector>
#include<queue>
#include <iostream>
using namespace std;

int solution(vector<vector<int> > maps)
{
    int dx[] = { 1, 0, -1, 0 };
    int dy[] = { 0, -1, 0, 1 };
    int row = maps[0].size();
    int col = maps.size();

    vector<vector<int>> visited;
    visited.resize(col, vector<int>(row, -1));

    queue<pair<int, int>> reservation;

    reservation.push({ 0, 0 });
    visited[0][0] = 1;

    while (reservation.empty() == false)
    {
        pair<int, int> now = reservation.front();
        reservation.pop();

        for (int i = 0; i < 4; ++i)
        {
            int x = now.second + dx[i], y = now.first + dy[i];

            if (x < 0 || x > row - 1 || y < 0 || y > col - 1)
                continue;

            if (maps[y][x] == 0)
                continue;

            if (visited[y][x] != -1)
                continue;

            reservation.push({ y, x });
            visited[y][x] = visited[now.first][now.second] + 1;
        }
    }

    return visited[col - 1][row - 1];
}

int main()
{
    vector<vector<int>> maps = { {1, 0, 1, 1, 1},{1, 0, 1, 0, 1},{1, 0, 1, 1, 1},{1, 1, 1, 0, 1},{0, 0, 0, 0, 1} };
    cout << solution(maps);

    return 0;
}