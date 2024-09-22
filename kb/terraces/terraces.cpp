/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/terraces
TAGS: dfs
EXPLANATION:
- For each cell A in the grid, if there is another cell B such that height[A] > height[B], then mark cell A as impossible 
- For each cell A in the grid, if A is marked impossible, use dfs (traverse up, down, left, right) to mark all cell C such that height[C] == height[A]
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
#define size(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
#define printDecimal(d) printf("%.9f\n", d)
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

const int mod = 1e9 + 7; 
const int inf = 0x3f3f3f3f;
 
template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second  << '\n'; }
template <class T>
void printArray(vector<T> arr) { for (int i = 0; i<size(arr); i++) {cout << arr[i] << " ";} cout << '\n'; } 

const int a[]{-1, 1, 0, 0};
const int b[]{0, 0, -1, 1};

int n,m; 

void dfs(int i, int j, vector<vector<bool>> &possible, vector<vector<int>> &grid) {
	possible[i][j] = false;
	for (int k = 0; k<4; k++) {
		int curr_x = i+a[k], curr_y = j+b[k];
		if (inrange(curr_x, 0, n-1) && inrange(curr_y, 0, m-1)) {
			if (possible[curr_x][curr_y] && grid[curr_x][curr_y] == grid[i][j]) dfs(curr_x, curr_y, possible, grid);
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> m >> n;
	vector<vector<int>> grid(n, vector<int>(m));
	vector<vector<bool>> possible(n, vector<bool>(m, true));
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<m; j++) cin >> grid[i][j];	
	}
	
	for (int i =0; i<n; i++) {
		for (int j = 0; j<m; j++) {
			for (int k = 0; k<4; k++) {
				int curr_x = i+a[k], curr_y = j+b[k];
				if (inrange(curr_x, 0, n-1) && inrange(curr_y, 0, m-1)) {
					if (grid[curr_x][curr_y] < grid[i][j]) possible[i][j] = false;
				}
			}
		}
	}
	
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<m; j++) {
			if (!possible[i][j]) dfs(i, j, possible, grid);
		}
	}
	
	int ret = 0;
	for (int i =0; i<n; i++) {
		for (int j =0; j<m; j++) {
			ret += possible[i][j];
		}
	}
	cout << ret << '\n';
}

