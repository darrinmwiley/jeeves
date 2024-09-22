/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/horror
TAGS: graph, bfs, breadth, breadth first search
EXPLANATION:
Do breadth first search starting with all movies on the horror list.
Nodes are movies, edges are between similar movies, all edge weights
re 1, and distances are horror indices. Store the accumulated distance
to each movie, with a large value being the default distance. Then,
iterate through the list of nodes and output the first ID with the
largest horror index.
END ANNOTATION
*/
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef pair<unsigned, unsigned> entry;

unsigned N, H, L;

int main()
{
	cin >> N >> H >> L;
	vector<unsigned> hIdx(N, numeric_limits<unsigned>::max());
	priority_queue<entry, vector<entry>, greater<entry>> Q;
	for (unsigned i = 0; i < H; i++)
	{
		unsigned x; cin >> x;
		hIdx[x] = 0;
		Q.push({ 0, x });
	}
	vector<vector<unsigned>> sim(N);
	for (unsigned i = 0; i < L; i++)
	{
		unsigned a, b; cin >> a >> b;
		sim[a].push_back(b);
		sim[b].push_back(a);
	}

	while (!Q.empty())
	{
		unsigned u = Q.top().second;
		Q.pop();
		for (unsigned v : sim[u])
		{
			if (hIdx[v] > hIdx[u] + 1)
			{
				hIdx[v] = hIdx[u] + 1;
				Q.push({ hIdx[v], v });
			}
		}
	}

	unsigned bestX = 0, bestHIdx = hIdx[0];
	for (unsigned x = 1; x < N; x++)
	{
		if (hIdx[x] > bestHIdx)
		{
			bestHIdx = hIdx[x];
			bestX = x;
		}
	}

	cout << bestX;

	return 0;
}