#include <iostream>
#include <vector>

#define MAX_VTXS 256

class AdjMatGraph
{
protected:
	int size;
	std::vector<char> vertices;
	std::vector<std::vector<int>> adj;
	//int adj[MAX_VTXS][MAX_VTXS];
public:
	AdjMatGraph() { reset(); }
	AdjMatGraph(int n) { reset(n); }
public:
	void insertVertex(char vertex)
	{
		if (!isFull())
			vertices[size++] = vertex;
	}

	void insertEdge(int from, int to)
	{
		setEdge(from, to, 1);
		setEdge(to, from, 1);
	}

	void display()
	{
		std::cout << "  ";

		for (int i = 0; i < size; ++i)
			std::cout << getVertex(i) << ' ';

		for (int y = 0; y < size; ++y)
		{
			std::cout << '\n' << getVertex(y) << ' ';

			for (int x = 0; x < size; ++x)
				std::cout << getEdge(y, x) << ' ';
		}
	}

	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }
	void reset(int n = 10)
	{
		size = 0;	
		vertices.resize(n);
		adj.resize(n, std::vector<int>(n));

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				setEdge(i, j, 0);
	}
};

int main()
{
	int n, m, temp1, temp2;
	std::cout << "정점의 개수와 간선의 수 :";
	std::cin >> n >> m;
	std::cout << "간선의 시작정점과 끝 정점 :" << std::endl;

	AdjMatGraph g;
	for (int i = 0; i < n; i++)
		g.insertVertex('A' + i);

	for (int i = 0; i < m; i++)
	{
		std::cin >> temp1 >> temp2;
		g.insertEdge(temp1, temp2);
	}

	std::cout << "인접 행렬로 표현한 그래프" << std::endl;
	g.display();
	return 0;


}