#include<iostream>
#include<queue>
#include<stack>
using namespace std;
int** create(int n)
{
	// recieve the number of nodes in the function
	int** a = new int*[n];
	for(int i = 0; i < n; i++)
		a[i] = new int[n];
	return a;
}
void addEdge(int** a, int i, int j)
{
	if(a[i][j])
	{
		cout << "Edge already exists" << endl; return;
	}
	a[i][j] = a[j][i] = 1;
}
void bfs(int** a, int n)
{
	bool* visited = new bool[n];
	for(int i = 0; i < n; i++)
		visited[i] = false;
	queue<int> q;
	cout << "Enter the element that you want to start with" << endl;
	int start;
	cin >> start;
	q.push(start);
	visited[start] = true;
	while(!q.empty())
	{
		int x = q.front();
		cout << x << " ";
		q.pop();
		for(int i = 0; i < n; i++)
		{
			if(a[x][i] && !visited[i])
			{
				q.push(i);
				visited[i] = true;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		if(visited[i]==false)
		{
			cout<<i<<" ";
		}
	}
	cout << endl;
	delete visited;
}
void dfs(int** a, int n)
{
	bool* visited = new bool[n];
	for(int i = 0; i < n; i++)
		visited[i] = false;
	stack<int> s;
	cout << "Enter the element that you want to start with" << endl;
	int start; cin >> start;
	s.push(start);
	visited[start] = true;
	while(!s.empty())
	{
		int x = s.top();
		cout << x << " ";
		s.pop();
		for(int i = 0; i < n; i++)
		{
			if(a[x][i] && !visited[i]) // If there is an  edge and not visited ith node,
									   // then control enters here.
			{
				s.push(i);
				visited[i] = true;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		if(visited[i]==false)
		{
			cout<<i<<" ";
		}
	}
	cout << endl;
	delete visited;
}
int main()
{
	cout << "Enter the number of nodes you want in the graph" << endl;
	int n;
	cin >> n;
	int** graph = create(n);
	/*addEdge(graph, 0, 1);
	addEdge(graph, 0, 6);
	addEdge(graph, 1, 2);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 3);
	addEdge(graph, 2, 3);
	addEdge(graph, 0, 3);
	addEdge(graph, 3, 4);
	addEdge(graph, 4, 1);*/
	addEdge(graph, 0,1);
	addEdge(graph, 0,2);
	addEdge(graph, 1,2);
	addEdge(graph, 2,0);
	addEdge(graph, 2,3);
	addEdge(graph, 3,3);
	bfs(graph, n); 			// Performing the Breadth First Search
	dfs(graph, n); 			// Performing the Depth First Search
}