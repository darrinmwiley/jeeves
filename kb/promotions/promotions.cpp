/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/promotions
TAGS: graph, directed acyclic graph, DAG, depth first search, DFS, recursion
EXPLANATION:
There are two (converse) dags involved: one mapping employees to those that are worse-performing (worse)
and one mapping employees to those that are better-performing (better). The number of employees reachable
from each employee x (including x themself) is computed. In the 1-indexed list of employees chosen to be
promoted, the minimum (best case) index of any employee x is just the number reachableon better; the maximum
(worst case) index of any employee x is just the total number of employees minus the number reachable on worse.
END ANNOTATION
*/
#include <iostream>
#include <vector>

using namespace std;

// Computes the number of elements reachable from x (including x itself) using depth first search
inline unsigned countReachable(unsigned x, const vector<vector<unsigned>>& graph, vector<bool>& visited)
{
	unsigned res = 1;
	for (unsigned y : graph[x])
		if (!visited[y])
		{
			visited[y] = true;
			res += countReachable(y, graph, visited);
		}
	return res;
}

int main()
{
	// Reads input data
	unsigned A, B, E, P;
	cin >> A >> B >> E >> P;

	// worse and better are converse directed acyclic graphs
	vector<vector<unsigned>> worse(E), better(E);
	for (unsigned i = 0; i < P; i++)
	{
		unsigned x, y;
		cin >> x >> y;
		worse[x].push_back(y);
		better[y].push_back(x);
	}
	vector<unsigned> maxIndex(E, numeric_limits<unsigned>::max()), minIndex(E);

	// Computes the the getSize function for each employee in both directions
	for (unsigned x = 0; x < E; x++)
	{
		vector<bool> visited(E, false);
		minIndex[x] = E - countReachable(x, worse, visited);
	}
	for (unsigned x = 0; x < E; x++)
	{
		vector<bool> visited(E, false);
		maxIndex[x] = countReachable(x, better, visited);
	}

	// Counts employees matching the criteria for each output
	unsigned certainPromoIfA = 0, certainPromoIfB = 0, certainNoPromoIfB = 0;
	for (unsigned x = 0; x < E; x++)
	{
		if (minIndex[x] < A)
			certainPromoIfA++;
		if (minIndex[x] < B)
			certainPromoIfB++;
		if (maxIndex[x] > B)
			certainNoPromoIfB++;
	}

	cout << certainPromoIfA << endl << certainPromoIfB << endl << certainNoPromoIfB;

	return 0;
}