/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/presidentialelections
TAGS: dp,binary search
EXPLANATION:
Step #1: Find required # of citizens that needs to be convinced so that the constituents can win in i-th state
Step #2: Use dp with the following states: dp[curr_#_of_delegates][curr_state]
Step #3: Use knapsack approach to evaluate dp
Step #4: Find min value required from dp[i], with i is min # of delegates required
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
const ll mod = 1e9 + 7;
 
template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(vector<T> arr) { for (int i = 0; i<size(arr); i++) {cout << arr[i] << " ";} cout << '\n'; } 

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<ll> delegates(n), constituents(n), federals(n), undecided(n), required(n);
	ll total_delegates = 0;
	for (int i = 0; i<n; i++) {
		cin >> delegates[i] >> constituents[i] >> federals[i] >> undecided[i];
		total_delegates += delegates[i];
	}
	for (int i = 0; i<n; i++) {
		ll low = 0, high = undecided[i], curr = inf;
		while (low <= high) {
			ll mid = low + (high - low)/2;
			if (constituents[i] + mid > federals[i] + undecided[i] - mid) curr = mid, high = mid-1;
			else low = mid+1;
		}
		required[i] = curr;
	} 
	vector<vector<ll>> dp(total_delegates + 1, vector<ll>(n+2, inf));
	for (int i = 0; i<=n; i++) dp[0][i] = 0;
	for (int i = 1; i<= total_delegates; i++) {
		for (int j = 1; j<=n; j++) {
			dp[i][j] = min(dp[i][j], dp[i][j-1]);
			if (i >= delegates[j-1]) dp[i][j] = min(dp[i][j], dp[i-delegates[j-1]][j-1] + required[j-1]);
			dp[i][n+1] = min(dp[i][n+1], dp[i][j]);
		}
	}
	ll ret = dp[total_delegates/2+1][n+1];
	for (int i = total_delegates/2 + 1; i <= total_delegates; i++) ret = min(ret, dp[i][n+1]);
	
	if (ret != inf) cout << ret << '\n';
	else cout << "impossible" << '\n';
}

/*
 * 
 * 
 * */
