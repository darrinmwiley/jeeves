/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/forestconstruction
TAGS: Forest, Tree, Graph, Constructive, Constructive Algorithm, Component, Connected Component
EXPLANATION:
First, assume that the given input describes a valid forest. Later, we will add tests to verify this. Also, assume v > 0. The trivial case of
v == 0 should be checked seperately.

First, compute the total degree of all vertices (td) and the number of edges (e = td / 2). It follows from Euler's formula for the number of faces in a
connected graph (by removing edges to disconnect the graph) that the number of components in this forest is k = v - e. We will construct a forest by
assigning an arbitrary collection of "internal" vertices (some may technically be leaves) to each component and satisfying their degrees by connecting
them to degree-one "leaf" vertices. Start by partitioning the vertices into two lists: the "leaves", which are all vertices with degree one, and the
"internal vertices", which are all other vertices. While the number of internal vertices is less than k, reassign leaf vertices as internal vertices.
Now, we will start to add edges, so keep track of an auxiliary array containing the "remaining degree" of each vertex (the degree minus the number of
edges added so far), initialized to be the same as the input degrees. First, sort the internal vertices by degree, ascending. Then, assign each of the
first k internal vertices to a new component. If there are more internal nodes than components, add all of the remaining internal vertices to the last
component. Add edges connecting each of these components to the previously added component. Be sure to update the remaining degree array as you go.
Then, add edges connecting leaves to each internal node until its remaining degree is satisfied. Once this is done, the forest is fully constructed.

Now, we must check the input to see whether it can describe a valid forest. Again, this assumes the v == 0 case has already been dealt with. If the
total degree is not even or the number of components is not positive, the input is invalid. Also, while adding the remaining internal vertices to
the last component, check whether we end up trying to add a connection to a vertex with a remaining degree of 0. If this happens, the input is
invalid. Otherwise, the process described above will construct a valid forest.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
	int v;
	cin >> v;
	if (v == 0)
	{
		cout << "POSSIBLE";
		return 0;
	}

	vector<int> D(v);
	for (int& d : D) cin >> d;
	int td = accumulate(D.begin(), D.end(), 0);
	int e = td / 2;
	int k = v - e;
	if (td % 2 != 0 || k <= 0)
	{
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}

	vector<pair<int, int>> ans;

	vector<int> L, I;
	for (int i = 0; i < v; i++)
		if (D[i] == 1)
			L.push_back(i);
		else
			I.push_back(i);

	while (I.size() < k)
	{
		int i = L.back();
		L.pop_back();
		I.push_back(i);
	}

	sort(I.begin(), I.end(), [&](int l, int r) -> bool
		{
			return D[l] < D[r];
		});

	vector<vector<int>> C(k);
	vector<int> CD(k, 0);
	for (int i = 0; i < k; i++)
	{
		C[i].push_back(I[i]);
		CD[i] += D[I[i]];
	}
	vector<int> D2 = D;
	for (int i = k; i < I.size(); i++)
	{
		pair<int, int> edge(C.back().back(), I[i]);
		C.back().push_back(I[i]);
		CD.back() += D[I[i]] - 2;

		if (min(--D2[edge.first], --D2[edge.second]) < 0)
		{
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
		ans.push_back(edge);
	}

	int l = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j : C[i])
		{
			while (D2[j] > 0)
			{
				D2[j]--;
				D2[L[l]]--;
				ans.emplace_back(j, L[l]);
				l++;
			}
		}
	}
	cout << "POSSIBLE" << endl;
	for (pair<int, int> edge : ans)
		cout << edge.first + 1 << ' ' << edge.second + 1 << endl;
}