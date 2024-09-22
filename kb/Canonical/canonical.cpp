/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/canonical
TAGS: dp,binary search
EXPLANATION:
Step #1: Construct table from 0 to sum of 2 largest denomination
Step #2: Use DP to construct the optimal solution
Step #3: Use binary search to find the largest denomination of the current price
Step #4: Check for each possible value if there is a difference between DP and greedy value
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

int search(vector<int> &a, int low, int high, int target) {
	int ret = 0;
	while (low <= high) {
		int mid = low + (high - low)/2;
		if (a[mid] <= target) {
			ret = mid;
			low = mid+1;
		}
		else high = mid-1;
	}
	return ret;
} 

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i<n; i++) cin >> a[i];
	int maxVal = a[n-1] + a[n-2];
	vector<int> dp(maxVal + 1, 1e9), greedy(maxVal + 1, 1e9);
	dp[0] = 0, greedy[0] = 0;
	for (int i = 1; i<=maxVal; i++) {
		for (int j = 0; j<n; j++) {
			if (i >= a[j]) dp[i] = min(dp[i], dp[i-a[j]] + 1);
		}
	}
	for (int i = 1; i<=maxVal; i++) {
		int idx = search(a, 0, n-1, i);
		greedy[i] = greedy[i-a[idx]] + 1;
	}
	bool canonical = true;
	for (int i = 1; i<=maxVal && canonical; i++) {
		if (greedy[i] != dp[i]) canonical = false;
	}
	cout << (canonical ? "canonical" : "non-canonical") << '\n';
}

