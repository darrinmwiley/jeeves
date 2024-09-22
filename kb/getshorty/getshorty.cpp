/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/getshorty
TAGS: graph theory, shortest path
EXPLANATION:
* This is a straight-forward implementation of Dijkstra's Algorithm
* The graph will have the intersections as vertices and corridor as edges
* => The problem becomes finding the path with max weight (weight being calculated by taking product of all edge weights)
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define umap unordered_map
#define size(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265

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
    int n,m; cin >> n >> m;
    while (n || m) {
        vector<double> dist(n, 0.0);
        vector<vector<pair<int, double>>> graph(n);
        for (int i= 0; i<m; i++) {
            int u,v;
            double d; cin >> u >> v >> d;
            graph[u].push_back(make_pair(v, d));
            graph[v].push_back(make_pair(u, d));
        }
        dist[0] = 1.0;
        auto comp = [dist](int a, int b) { 
            if (dist[a] != dist[b]) return dist[a] > dist[b]; 
            return a < b;
        };
        set<int, decltype(comp)> q(comp);
        q.insert(0);
        
        while (!q.empty()) {
            int curr = *q.begin();
            q.erase(q.begin());
            
            for (int i= 0; i<size(graph[curr]); i++) {
                int dest = graph[curr][i].first;
                double d = graph[curr][i].second;
                if (dist[dest] < dist[curr] * d) {
                    q.erase(dest);
                    dist[dest] = dist[curr] * d;
                    q.insert(dest);
                }
            }
        }
        
        printDecimal(4) << dist[n-1] << '\n';
        cin >> n >> m;
    }
} 
