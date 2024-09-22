/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/nikola
TAGS: dp
EXPLANATION:
- Let dp[pos][j] be min cost if Nikola reaches pos-th square with a jump of length "j"
=> To reach pos with j jumps, Nikola had to reach either (pos - j)-th square with a jump of length (j-1) or (pos + j)-th square with a jump of length (j) before that (*)
=> We have dp relation: dp[pos][j] = min(dp[pos-j][j-1], dp[pos+j][j]) + cost[pos] (cost[pos] is entry fee for pos-th square)
- The most optimal solution will dp[n][j] for every possible j
- (*): Make sure to check if pos-j and pos+j are valid square
- Base case would be dp[2][1] = cost[2]
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define umap unordered_map
#define size(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "Yes": "No") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

const ll inf = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(vector<T> arr) { for (int i = 0; i<size(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T> 
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }}


int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> a(n);
	read(a, n);
	vector<vector<int>> dp(n, vector<int>(n, inf));
	dp[0][0] = 0, dp[1][1] = a[1];
	for (int j =1; j<n; j++) {
		for (int i = n-1; i>=0; i--) {
			if (dp[i][j] != inf) continue;
			if (inrange(i-j, 0, n-1)) dp[i][j] = min(dp[i][j], dp[i-j][j-1] + a[i]);
			if (inrange(i+j, 0, n-1)) dp[i][j] = min(dp[i][j], dp[i+j][j] + a[i]);
		}
	}
	
	int ret = dp[n-1][0];
	for (int i = 1; i<n; i++) ret = min(ret, dp[n-1][i]);
	cout << ret << '\n';
 }   
