/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/marypartitions
TAGS: dp
EXPLANATION:
* Given dp[n][idx] as the numbers of ways to partition n from the first "idx + 1" powers of 3
* => At that point, dp[n][idx] can be reached from either dp[n - pow_of_m[idx]][idx] or dp[n][idx-1]
* => dp[n][idx] = dp[n-pow_m[idx]][idx] + dp[n][idx-1]
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

const ll inf = 0x3f3f3f3f;

template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(vector<T> arr) { for (int i = 0; i<size(arr); i++) {cout << arr[i] << " ";} cout << '\n'; } 

int evaluate(int n, int idx, vector<int> &powm, vector<vector<int>> &dp) {
	if (n < 0) return 0;
	if (dp[n][idx] != 1e9) return dp[n][idx];
	int curr = evaluate(n - powm[idx], idx, powm, dp) + evaluate(n, idx-1, powm, dp);
	return dp[n][idx] = curr;	
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int cases, m, n; cin >> cases >> m >> n;
		int curr = 1;
		vector<int> powm;
		while (curr <= n) {
			powm.push_back(curr);
			curr *= m;
		}
		vector<vector<int>> dp(n+1, vector<int>(size(powm), 1e9));
		for (int i = 0; i<=n; i++) dp[i][0] = 1;
		
		int ret = evaluate(n, size(powm)-1, powm, dp);
		cout << cases << " " << ret << '\n';
	}
}

