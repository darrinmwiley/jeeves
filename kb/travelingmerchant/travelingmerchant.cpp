/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/travelingmerchant
TAGS: range queries, segment tree
EXPLANATION:
Assume all paths are forwards
The cycle of days is offset by 7, so the problem can instead be represented as 7 possible constant arrays, 
based on starting point. The problem can be solved with a segment tree.

For each range, store the max value, minimum value, and max possible profit.
In order to update a range, updating the max and min is simple.
To update the max possible profit, notice that either
 - both buy and sell day are in the left half
 - both buy and sell day are in the right half
 - the buy day is in the left half and the sell day is in the right half
The first two cases are accounted for by common segment tree implementations
The third case is accounted for by the min value in the left half, and max value in the right half

To account for backwards arrays, the array can be reversed and solved alongside the rest of the problem.

This gives 7*2 = 14 possible arrays and segment trees to account for

END ANNOTATION
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int v[100000], d[100000];
int N;
typedef pair<int, int> pii;
typedef pair<int, pii> pip;

typedef struct TreeNode {
	TreeNode *l, *r;
	int b, e;
	int mx, mn, rg;
	TreeNode() {
		l = r = nullptr;
	}
	TreeNode(int bb, int ee) {
		b = bb; e = ee;
		if (b != e) {
			int m = (b + e) / 2;
			l = new TreeNode(b, m);
			r = new TreeNode(m + 1, e);
		}
	}
	void add(int ind, int v) {
		if (e < ind || b > ind) return;
		if (b == e) {
			mx += v;
			mn += v;
			rg = 0;
			return;
		}
		l->add(ind, v);
		r->add(ind, v);
		pull();
	}
	
	pip get(int bb, int ee) {
		if (e < bb || b > ee) return make_pair(-1, make_pair(0, 0));
		if (e <= ee && b >= bb) {
			return make_pair(rg, make_pair(mx, mn));
		}
		pip pl = l->get(bb, ee);
		pip pr = r->get(bb, ee);
		if (pl.first == -1) return pr;
		if (pr.first == -1) return pl;
		int mxx = max(pl.second.first, pr.second.first);
		int mnn = min(pl.second.second, pr.second.second);
		int rgg = max(pr.second.first - pl.second.second, max(pl.first, pr.first));
		return make_pair(rgg, make_pair(mxx, mnn));
	}

	void pull() {
		mx = max(l->mx, r->mx);
		mn = min(l->mn, r->mn);
		rg = max(r->mx - l->mn, max(l->rg, r->rg));
	}

} Node;

Node* seg[7];
Node* rseg[7];
int arr[7][100000];

int cost(int v, int d, int day) {
	return v + (3 - abs(3 - day))*d;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> v[i] >> d[i];
	}
	for (int s = 0; s < 7; s++) {
		seg[s] = new Node(0, N - 1);
		int day = s;
		for (int i = 0; i < N; i++) {
			arr[s][i] = cost(v[i], d[i], day);
			day++;
			if (day == 7) day = 0;
			seg[s]->add(i, arr[s][i]);
		}
	}
	for (int i = 0; i < N - 1 - i; i++) {
		swap(v[i], v[N - 1 - i]);
		swap(d[i], d[N - 1 - i]);
	}
	for (int s = 0; s < 7; s++) {
		rseg[s] = new Node(0, N - 1);
		int day = s;
		for (int i = 0; i < N; i++) {
			arr[s][i] = cost(v[i], d[i], day);
			day++;
			if (day == 7) day = 0;
			rseg[s]->add(i, arr[s][i]);
		}
	}

	int Q;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int s, t;
		cin >> s >> t;
		s--; t--;
		if (s < t) {
			int m = 7 - (s % 7);
			if (m == 7) m = 0;
			cout << seg[m]->get(s, t).first << endl;
		}
		else {
			s = N - 1 - s;
			t = N - 1 - t;
			int m = 7 - (s % 7);
			if (m == 7) m = 0;
			cout << rseg[m]->get(s, t).first << endl;
		}
	}



	return 0;
}