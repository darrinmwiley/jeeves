/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/islands2
TAGS: Geometry, Math, Brute Force, Graph, Graphs, Graph Theory, Directed Graph, Directed Graphs, Components, Strongly Connected Components, Strong Connectivity, Connectivity, Digraph, Digraphs, Directed Acyclic Graph, DAG, DFS, Depth-First Search, Depth First Search
EXPLANATION:
First, compute which island each tree belongs to. This can be done in O(n * m) by brute-forcing all tree-island pairs with some basic geometry.
(The distance from the tree to the island center should be at most the island's radius.)

Next, we need to determine, for each ordered pair of distinct islands, whether we can throw an item from the first island to the second. This can again be brute-forced
in O(n * m) by checking, for each tree, which islands besides the island it is on are within its throwing range.
(The distance from the tree to the island should be at most the island's radius plus the tree's height times k).
Record these pairs as edges in a digraph (represented by an adjacency matrix).

Now, identify all strongly connected components (henceforth called clusters) in this digraph (using i.e. Kosajaru's Algorithm).
The goal is to make the whole digraph strongly connected by possibly adding a single undirected edge.

We can now compute the minimum tunnel lenth between each pair of distinct clusters in O(n^2) easily by brute-forcing all pairs of islands.
Note that the problem requires that each tunnel endpoint is at least 100cm away from the shore.
Thus, after finding the distance between the island centers and subtracting their radii, you must also add 200cm.

Now, consider a digraph in which we collapse all clusters into single vertices.
There is an edge from cluster a to cluster b in this new graph iff there was an edge from some vertex in cluster a to some vertex in cluster b in the original.
No set of at least 2 vertices in this new graph may be strongly connected, because then they would be strongly connected in the original graph.
This implies that there are no cycles (this new graph is a DAG), vertices in a cycle are strongly connected.

In order to make the graph strongly connected by adding a single undirected edge, consider the following possibilities:
1) There is only one cluster and the answer is 0.
2) There are only two clusters and we can simply connect them.

If none of these apply, we must find the DAG's source (indegree-0) and sink (outdegree-0) vertices.
There must be at least one of each, or else we could form a cycle by repeatedly following edges backwareds or forwards, respectively.
If there is exactly one of each, we can simply connect the source to the sink.
Since the source can reach everything, everything can reach the sink, and the sink can now reach the source, the whole graph is strongly connected.
If there are multiple sources, it is impossible to connect a sink to all of them, and if there are multiple sinks, it is impossible to connect all of them to a source.
Thus, if none of the previous cases apply and there is not exactly one source and one sink, the answer is impossible.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>
#include <math.h>
#include <numeric>
#include <unordered_set>
#include <vector>

using namespace std;

struct circle
{
	int x, y, r;
};

inline constexpr int64_t dist2(int x1, int y1, int x2, int y2)
{
	int64_t dx = x1 - x2, dy = y1 - y2;
	return dx * dx + dy * dy;
}

inline long double dist(int x1, int y1, int x2, int y2)
{
	return sqrtl(dist2(x1, y1, x2, y2));
}

// Phase 1 of Kosaraju's Algorithm
inline void kosaraju1(const vector<vector<bool>>& graph, vector<int>& dfsOrder, vector<bool>& visited, int v)
{
	if (visited[v])
		return;
	visited[v] = true;
	for (int w = 0; w < graph.size(); w++)
		if (graph[v][w])
			kosaraju1(graph, dfsOrder, visited, w);
	dfsOrder.push_back(v);
}

// Phase 2 of Kosaraju's Algorithm
inline void kosaraju2(const vector<vector<bool>>& graph, vector<int>& clusters, int cluster, int v)
{
	if (clusters[v] >= 0)
		return;
	clusters[v] = cluster;
	for (int w = 0; w < graph.size(); w++)
		if (graph[w][v])
			kosaraju2(graph, clusters, cluster, w);
}


int main()
{
	// I/O
	int n, m, k;
	std::cin >> n >> m >> k;

	// Islands
	vector<circle> islands(n);
	// Tree ranges
	vector<circle> trees(m);
	// Tree -> Island map
	vector<int> islandMap(m, -1);

	for (circle& is : islands)
		cin >> is.x >> is.y >> is.r;
	for (circle& tr : trees)
	{
		cin >> tr.x >> tr.y >> tr.r;
		tr.r *= k;
	}

	// Identify each tree's island
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (dist2(trees[i].x, trees[i].y, islands[j].x, islands[j].y) <= (int64_t)islands[j].r * islands[j].r)
			{
				islandMap[i] = j;
				break;
			}

	// Construct digraph of islands with edges corresponding to valid tree throws.
	vector<vector<bool>> graph(n, vector<bool>(n, false));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			if (j == islandMap[i])
				continue;
			int64_t r = trees[i].r + islands[j].r;
			if (dist2(trees[i].x, trees[i].y, islands[j].x, islands[j].y) <= r * r)
				graph[islandMap[i]][j] = true;
		}

	// Find island clusters (strongly-connected components in graph) using Kosaraju's Algorithm.
	vector<int> dfsOrder;
	dfsOrder.reserve(n);
	vector<bool> visited(n);
	for (int v = 0; v < n; v++)
		kosaraju1(graph, dfsOrder, visited, v);

	vector<int> clusters(n, -1);
	int c = 0;

	while (!dfsOrder.empty())
	{
		int v = dfsOrder.back();
		dfsOrder.pop_back();
		if (clusters[v] < 0)
			kosaraju2(graph, clusters, c++, v);
	}

	// If the islands are already strongly conected, no tunnel is needed.
	if (c == 1)
	{
		cout << 0 << endl;
		return 0;
	}

	// Find the minimum tunnel length for each pair of clusters.
	vector<vector<long double>> clusterDist(c, vector<long double>(c, numeric_limits<long double>::infinity()));
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			int a = clusters[i], b = clusters[j];
			if (a == b)
				continue;
			if (a > b)
				swap(a, b);
			long double d = dist(islands[i].x, islands[i].y, islands[j].x, islands[j].y) - islands[i].r - islands[j].r + 200;
			if (d < clusterDist[a][b])
				clusterDist[a][b] = d;
		}

	// If there are only two clusters, connect them.
	if (c == 2)
	{
		cout << fixed << setprecision(7) << clusterDist[0][1] << endl;
		return 0;
	}

	// Find source and sink clusters.
	unordered_set<int> sources, sinks;
	for (int i = 0; i < c; i++)
	{
		sources.insert(i);
		sinks.insert(i);
	}
	for (int v = 0; v < n; v++)
	{
		// Detect edges crossing clusters.
		for (int w = 0; w < n; w++)
			if (graph[v][w])
			{
				if (clusters[v] == clusters[w])
					continue;
				sinks.erase(clusters[v]);
				sources.erase(clusters[w]);
			}
	}

	// Connect the only source with the only sink if possible.
	if (sources.size() == 1 && sinks.size() == 1)
	{
		int a = *sources.begin(), b = *sinks.begin();
		cout << fixed << setprecision(7) << clusterDist[min(a, b)][max(a, b)];
	}
	else
		cout << "impossible";
}