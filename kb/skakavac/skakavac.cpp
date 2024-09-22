/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/skakavac
TAGS: Segment Tree, Range, Range Max, LIS, Longest Increasing Subsequence, Grid, Dynamic Programming, DP
EXPLANATION:
Note: If you are using this approach, it is recommended that you implement it in C++. This implementation has a runtime of 5.86 seconds, while the maximum is 6. Due to the
large input size, fast I/O is also recommended.

This problem can be thought of as finding the longest decreasing subsequence of any sequence of points satisfying the given constraints ending at (R, C). Thus, the following DP
approach gives the correct answer (slowly). Create a list of 1e6 lists numbered 0 to 999999. For each flower at (i, j) with p petals, add it to list (1e6 - p). This reverse
ordering converts the problem to Longest Increasing Subsequence. Then, for each list in order, compute the LIS of each flower. This is simply one plus the maximum LIS of all
cells reachable from it in one step. Note that the changes for a list of flowers with the same number of petals must be applied to the grid after all values have been computed
for that list. Otherwise, a sequence consisting of multiple flowers with the same number of petals could be formed. This algorithm runs too slowly (O(n^3)), but it can be
accelerated.

First, consider the simple 1D LIS problem. This can be solved by processing the elements in ascending order by value, as above. The "reachable elements" are just the elements
before the current one in the original array. The new LIS for a value can be computed by finding the maximum LIS in the portion of the array preceding the current element
plus one. While this is normally O(n^2) assuming the values in the array are O(n), it can be sped up to O(nlg(n)) by storing the LIS values in a range-max segment tree, which
reduces each range max query to O(lg(n)). This differs from the usual O(nlg(n)) approach and has larger constant factors, but it is easier to extend to the above problem.

Note that the "reachable elements" fall into 8 separate ranges, each of which is a 1-wide strip of elements parallel to one axis of the grid. Instead of storing the maximum
LIS values in a grid, store them in two arrays of n range-max segment trees: one with a tree for each row and one with a tree for each column. Then, processing each flower
only requires 8 range-max calls and a point update for storing the LIS length. Thus, the whole algorithm runs in O(m + n^2lg(m)) (where m is the maximum number of petals on a
flower, assumed to be 1e6) with a large-ish constant factor.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct SegTree
{
	int n;
	int m;
	vector<vector<int>> data;

	inline SegTree(int n) :
		n(n - 1), m(0)
	{
		for (int k = 0; k < 5; k++)
			this->n |= this->n >> (1 << k);
		this->n++;
		m = 0;
		for (int n2 = this->n; n2; n2 /= 2)
			m++;

		data.reserve(m);
		for (int i = 0; i < m; i++)
			data.push_back(vector<int>(1 << i, 0));
	}

	void update(int idx, int val)
	{
		data.back()[idx] = val;
		for (int i = idx / 2, l = m - 2; l >= 0; i /= 2, l--)
			data[l][i] = max(data[l + 1][i * 2], data[l + 1][i * 2 + 1]);
	}

	inline int query(int lo, int hi, int nlo, int nhi, int l, int i) const
	{
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (lo > hi)
			return 0;
		if (lo == nlo && hi == nhi)
			return data[l][i];
		int mid = (nlo + nhi) / 2;
		return max(query(lo, hi, nlo, mid, l + 1, i * 2), query(lo, hi, mid + 1, nhi, l + 1, i * 2 + 1));
	}

	inline int query(int lo, int hi) const
	{
		return query(lo, hi, 0, n - 1, 0, 0);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, r0, c0;
	cin >> n >> r0 >> c0;
	r0--; c0--;

	vector<vector<int>> G(n, vector<int>(n));
	for (vector<int>& g : G) for (int& gg : g)
		cin >> gg;

	vector<SegTree> R, C;
	R.reserve(n); C.reserve(n);
	for (int i = 0; i < n; i++)
	{
		R.emplace_back(n);
		C.emplace_back(n);
	}

	vector<vector<pair<int, int>>> ID(1'000'000);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
		ID[1'000'000 - G[i][j]].emplace_back(i, j);

	vector<pair<pair<int, int>, int>> upd;
	for (const vector<pair<int, int>>& id : ID)
	{
		if (id.empty()) continue;
		upd.clear();
		for (const pair<int, int>& ij : id)
		{
			const int& i = ij.first, &j = ij.second;
			int v = 0;
			if (i > 0)
			{
				v = max(v, R[i - 1].query(0, j - 2));
				v = max(v, R[i - 1].query(j + 2, n - 1));
			}
			if (i < n - 1)
			{
				v = max(v, R[i + 1].query(0, j - 2));
				v = max(v, R[i + 1].query(j + 2, n - 1));
			}
			if (j > 0)
			{
				v = max(v, C[j - 1].query(0, i - 2));
				v = max(v, C[j - 1].query(i + 2, n - 1));
			}
			if (j < n - 1)
			{
				v = max(v, C[j + 1].query(0, i - 2));
				v = max(v, C[j + 1].query(i + 2, n - 1));
			}
			upd.emplace_back(ij, 1 + v);
		}
		for (const pair<pair<int, int>, int>& u : upd)
		{
			const int& i = u.first.first, &j = u.first.second, &v = u.second;
			R[i].update(j, v);
			C[j].update(i, v);
		}
	}

	cout << R[r0].query(c0, c0);
}