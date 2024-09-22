/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/island
TAGS: union-find
EXPLANATION:
To find the number of islands, we can use union find to connect ('X' and '#') and ('#' and '#'). The number of 
non-water connected components is the number of islands

To find the number of bridges, we can look at every 'X', and count the number of bridges that it is the endpoint of.
Sum it up and divide by two to account for the fact that there are two endpoints on every bridge.

Afterwards, use union find to connect ('X' and 'B') and ('B' and 'B'), and the number of non-water components is the number
of buses needed

END ANNOTATION
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int N;
int M;
string grid[80];
int par[6400];
set<int> pars;

int find(int a) {
	if (a == par[a]) return a;
	return (par[a] = find(par[a]));
}

void merge(int a, int b) {
	if (a < 0 || a >= N * M || b < 0 || b >= N * M) return;
	a = find(a);
	b = find(b);
	par[a] = b;
}

bool land(char c) {
	return ((c == 'X') || (c == '#'));
}

bool bridged(char c1, char c2) {
	if (c1 == 'X') swap(c1, c2);
	if (c2 == 'X') {
		return (c1 == '#' || c1 == 'B');
	}
	return (c2 == c1 && c1 == 'B');
}

int bridge(int r, int c) {
	int res = 0;
	if (r > 0 && grid[r - 1][c] == 'B') res++;
	if (c > 0 && grid[r][c - 1] == 'B') res++;
	if (r < N-1 && grid[r + 1][c] == 'B') res++;
	if (c < M-1 && grid[r][c + 1] == 'B') res++;
	return res;
}

void process() {
	M = grid[0].size();
	for (int i = 0; i < N*M; i++) par[i] = i;
	for (int i = 1; i < N; i++) {
		for (int e = 1; e < M; e++) {
			if (land(grid[i][e]) && land(grid[i - 1][e])) {
				merge(i*M + e, (i - 1)*M + e);
			}
			if (land(grid[i][e]) && land(grid[i][e - 1])) {
				merge(i*M + e, (i)*M + e - 1);
			}
		}
	}
	for (int i = 1; i < N; i++) {
		if (land(grid[i][0]) && land(grid[i - 1][0])) {
			merge(i*M, (i - 1)*M);
		}
	}
	for (int i = 1; i < M; i++) {
		if (land(grid[0][i]) && land(grid[0][i - 1])) {
			merge(i, i-1);
		}
	}

	int xcount = 0;
	int isl = 0;
	for (int i = 0; i < N*M; i++) {
		if (land(grid[i / M][i%M])) {
			if (par[i] == i) isl++;
		}
		if (grid[i / M][i%M] == 'X') {
			xcount += bridge(i/M, i%M);
		}
	}
	xcount /= 2;

	cout << "islands: " << isl << endl;
	cout << "bridges: " << xcount << endl;

	for (int i = 1; i < N; i++) {
		for (int e = 1; e < M; e++) {
			if (bridged(grid[i][e], grid[i-1][e])) {
				merge(i*M + e, (i - 1)*M + e);
			}
			if (bridged(grid[i][e], grid[i][e-1])) {
				merge(i*M + e, (i)*M + e - 1);
			}
		}
	}
	for (int i = 1; i < N; i++) {
		if (bridged(grid[i][0], grid[i-1][0])) {
			merge(i*M, (i - 1)*M);
		}
	}
	for (int i = 1; i < M; i++) {
		if (bridged(grid[0][i], grid[0][i-1])) {
			merge(i, i - 1);
		}
	}

	isl = 0;
	for (int i = 0; i < N*M; i++) {
		if (land(grid[i / M][i%M])) {
			if (par[i] == i) isl++;
		}
	}
	cout << "buses needed: " << isl << endl;
}

int main()
{
	string s;
	int cnt = 1;
	while (getline(cin, s)) {
		N = 0;
		while (s != "") {
			grid[N] = s;
			N++;
			getline(cin, s);
		}
		cout << "Map " << cnt << endl;
		process();
		cnt++;
	}

	return 0;
}