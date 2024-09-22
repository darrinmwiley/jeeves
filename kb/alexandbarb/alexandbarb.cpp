/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/alexandbarb
TAGS: math, observation, dp
EXPLANATION:
- Let dp[i] be True if Alex can win if there are i cards on the stack initially
- When using dp on small dataset, it is possible to see that dp[i] = dp[i+n+m] for all i 
=> It is possible to say that dp[k] = dp[k%(n+m)]
- For all i in the range of [0, n+m-1]: dp[i] is False only when i < m

=> Approach: If (k%(n+m) < m), then Barb will win, else Alex wins
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "Yes": "No") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265
 
//const int inf = 0x3f3f3f3f;
const ll inf = 1e15;
const ll mod = 1e9 + 7;
 
template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(vector<T> arr) { for (int i = 0; i<len(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T> 
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }} 
template<class T>
void printGrid(vector<vector<T>> &grid) {for (int i =0; i<len(grid); i++) {for (int j =0; j<len(grid[i]); j++) { cout << grid[i][j] << " ";}cout << '\n';}}
template<class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }

#define prayGod main

int prayGod() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int k,m,n; cin >> k >> m >> n;
    k %= (n+m);
    if (k < m) cout << "Barb" << '\n';
    else cout << "Alex" << '\n';
} 

