/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/companypicnic
TAGS: DFS, Depth First Search, DP, Dynamic Programming, Tree, Graph, Tree DP, Tree Dynamic Programming
EXPLANATION:
First, generate a tree from the input rooted at the CEO. For each node in depth-first order, we can compute the following information:
1) The optimal result for the subtree rooted at the node, assuming the node is not the higher-ranking member of a team
2) The optimal result for the subtree rooted at the node with no restricitons

For both cases, we compute a pair consisting of the number of teams formed and the total speed of all teams. A pair is more optimal if is greater lexicographically.

For case (1), we simply add case (2) for the subtrees rooted at all children. (If there are no children, the result is trivially (0, 0.0).) This is because if the
current node is not the higher-ranking member of a team, its children are not the lower-ranking member of a team, so there is no restriction on whether or not they
can be the higher-ranking member of a team.

For case (2), there are several options; the optimal result is the maximum of them. The first option is to simply not be a member of the higher-ranking team, which
is just case (1). If the node is a leaf, this is the only option. Otherwise, for each child, there is the option to form a team with the current node and that child.
This can be computed from the result of case (1). First, subtract the child's case (2) and add its case (1). This correpsonds to the fact that the child cannot be
the higher-ranking member of a team, as it is already the lower-ranking member of a team. Then, add 1 to the number of teams and the minimum speed of the current node
and the current child to the total speed.

The overal answer is case (2) for the ceo. This algorithm runs in linear time because there is a constant amount of work done per node (charging the computation of
case (2) to the child nodes).
END ANNOTATION
*/

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

int n;
vector<vector<int>> G;
vector<double> SP;

vector<pair<pair<int, double>, pair<int, double>>> DP;

void dfs(int u)
{
	for (int v : G[u])
		dfs(v);

	pair<pair<int, double>, pair<int, double>> ans{ make_pair(0, 0.), make_pair(0, 0.) };
	for (int v : G[u])
	{
		ans.first.first += DP[v].second.first;
		ans.first.second += DP[v].second.second;
	}
	ans.second = ans.first;
	for (int v : G[u])
	{
		pair<int, double> incAns = ans.first;
		incAns.first -= DP[v].second.first;
		incAns.second -= DP[v].second.second;
		incAns.first += DP[v].first.first;
		incAns.first++;
		incAns.second += DP[v].first.second;
		incAns.second += min(SP[u], SP[v]);
		ans.second = max(ans.second, incAns);
	}
	DP[u] = ans;
}

int main()
{
	cin >> n;
	G.resize(n);
	SP.resize(n);
	int ceo;
	{
		vector<pair<int, int>> E;
		string n1, n2;
		double sp;
		unordered_map<string, int> ID;
		for (int i = 0; i < n; i++)
		{
			cin >> n1 >> sp >> n2;
			bool isCeo = n2 == "CEO";
			if (isCeo) n2 = n1;
			int i1 = ID.try_emplace(n1, ID.size()).first->second;
			int i2 = ID.try_emplace(n2, ID.size()).first->second;
			if (isCeo) ceo = i2;
			else E.emplace_back(i1, i2);
			SP[i1] = sp;
		}
		for (pair<int, int> e : E)
			G[e.second].push_back(e.first);
	}

	DP.resize(n, { make_pair(-1, 0), make_pair(-1, 0) });
	dfs(ceo);
	pair<int, double> ans = DP[ceo].second;
	ans.second /= ans.first;
	cout << ans.first << ' ' << fixed << setprecision(5) << ans.second;
}