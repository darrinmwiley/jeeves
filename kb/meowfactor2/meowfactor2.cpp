/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/meowfactor2
TAGS: dp, bfs
EXPLANATION:
- Generate all permutations of "meow" along with # of operations necessary to convert "meow" to the specific permutation using BFS shortest path
- For each generated permutation, apply Edit Distance DP between s and the the current permutation
=> Result will be the most optimal value gained from DP + # of operations needed to convert "meow" to current permutation
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
#define size(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printArray(arr) for (int i = 0; i<size(arr); i++) cout << arr[i] << " ";cout << '\n'
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
#define printDecimal(d) printf("%.9f\n", d)
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
 
const int inf = 0x3f3f3f3f;
 
template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) {cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n';}
template <class T1, class T2>
void printPair(pair<T1, T2> p) {cout << p.first << " " << p.second << '\n';}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	string s; cin >> s;
	unordered_map<string, int> perm;
	deque<string> Q;
	Q.push_back("meow");
	perm["meow"] = 0;
	while (!Q.empty()) {
		string curr = Q.front(), temp = curr;
		Q.pop_front();
		for (int i = 0; i<3; i++) {
			swap(temp[i], temp[i+1]);
			if (!present(perm, temp) || perm[temp] > perm[curr] + 1) {
				perm[temp] = perm[curr] + 1;
				Q.push_back(temp);
			}
			swap(temp[i], temp[i+1]);
		}
	}
	int ret = 1e9, n = size(s)+1, m = 5;
	int dp[n][m];
	for (auto it = perm.begin(); it != perm.end(); it++) {
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i<m; i++) dp[0][i] = dp[0][i-1] + 1;
		for (int i = 1; i<n; i++) {
			for (int j = 1; j<m; j++) {
				dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
				if (s[i-1] == it->first[j-1]) dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
			}
		}
		int curr = dp[0][m-1];
		for (int i = 1; i<n; i++) curr = min(curr, dp[i][m-1]);
		ret = min(ret, curr + it->second);
	}
	cout << ret << '\n';
}

