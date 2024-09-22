/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/allpairspath
TAGS: floyd-warshall
EXPLANATION:
- This is just implementation of Floyd Warshall Algorithm, but here are a few things to beware:
  + Parallel edges exist
  + Negative edges exist => negative cycles may also exist 
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
 
const int inf = 0x3f3f3f3f;
//const ll inf = 1e18;
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
void printGrid(vector<vector<T>> &grid) {for (int i =0; i<len(grid); i++) {for (int j =0; j<len(grid[i]); j++) { cout << grid[i][j] << '\t';}cout << '\n';}}
template<class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }

#define prayGod main

int prayGod() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m,q; cin >> n >> m >> q;
    while (n || m || q) {
        vector<vector<int>> dist(n, vector<int>(n, inf));
        for (int i = 0; i<m; i++) {
            int u,v,w; cin >> u >> v >> w;
            dist[u][v] = min(dist[u][v], w);
        }
        for (int i = 0; i<n; i++) dist[i][i] = 0;
        for (int k = 0; k<n; k++) {
            for (int i = 0; i<n; i++) {
                for (int j = 0; j<n; j++) {
                    if (dist[i][k] < inf && dist[k][j] < inf) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<n; j++) {
                for (int k = 0; k<n; k++) {
                    if (dist[i][k] < inf && dist[k][j] < inf && dist[k][k] < 0) dist[i][j] = -inf;
                }
            }
        }
        while (q--) {
            int u,v; cin >> u >> v;
            if (dist[u][v] >= inf) cout << "Impossible" << '\n';
            else if (dist[u][v] <= -inf) cout << "-Infinity" << '\n';
            else cout << dist[u][v] << '\n';
        }
        cout << '\n';
        cin >> n >> m >> q;
    }
    
} 