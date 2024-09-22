/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/heartrate
TAGS: math
EXPLANATION:
- BPM = 60*b/p
- Low ABPM = 60 * (b-1) / p
- High ABPM = 60 * (b+1) / p
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
	int t; cin >> t;
	while (t--) {
		double b,p; cin >> b >> p;
		double bpm = b*60/p, high = 60*(b+1)/p, low = 60*(b-1)/p;
		printDecimal(4) << low << " " << bpm << " " << high << '\n';
	}
 }  
