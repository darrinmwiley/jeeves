/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/folding
TAGS: Graph Theory
EXPLANATION:
We turn each sheet of paper into a line segment. At the end, we want these
line segments stacked so that the segment for 1 is on top, then 2, etc. Visualization:
+------1-------+
+------2-------+
+------3-------+
+------4-------+
We can think of folds as an edge between two left or two right endpoints of these line segments.
To solve the problem, we need only find out if our folds cross each other. You can test this yourself on 41325(NO), 31542(YES), 1324(NO)
Our folds can be thought of as line segments belonging either to the left or to the right. 
It's sufficient that these line segments don't intersect (for the folds to not cross)
Efficiency determining this is up to the reader but you can reference what I did below
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) ((i) >= (a) && (i) <= (b))

#define mp make_pair
#define mt make_tuple

using pii = pair<int,int>;
using ll = long long;


const int N = 1e6;
vector<int> adj[N];

void addEdge(int i, int j) {
	adj[i].push_back(j);
	adj[j].push_back(i);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;

	int a[n];
	f(i,0,n) {
		cin>>a[i];
		a[i]--;
	}
	vector<pii> gro[2];
	int gr = 0;

	int v = 0;
	f(i,0,n) if (a[i] == 0) v = i;

	f(i,v+1,n) {
		int x = a[i-1];
		int y = a[i];
		if (x > y) swap(x,y);

		gro[gr].push_back(mp(x,y));
		
		gr ^= 1;
	}
	gr = 1;

	fr(i,0,v) {
		int x = a[i];
		int y = a[i+1];
		if (x > y) swap(x,y);

		gro[gr].push_back(mp(x,y));
		gr ^= 1;
	}

	bool gd = 1;
	f(z,0,2) {
		sort(begin(gro[z]), end(gro[z]));

		// Hint: Determining if a collection of intervals cross
		priority_queue<int, vector<int>, greater<int>> pq;
		f(i,0,gro[z].size()) {
			while (pq.size() && pq.top() < gro[z][i].first) pq.pop();
			if (pq.size() && pq.top() <= gro[z][i].second) gd = 0;

			pq.push(gro[z][i].second);
		}
		// End hint
	}

	cout << (gd ? "YES":"NO") << endl;


	return 0;
}
