/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/treehouses
TAGS: dsu, mst
EXPLANATION:
* Create n+1 disjoint sets, the first n sets will be for the first n treehouses, and the last one will be for the open land
* Merge the first e trees with the open land
* Do Krusal MST until all treehouses and the open land are connected 
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;
 
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
// const ll inf = 1e18;
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

int find_rep(int u, vector<int> &union_data) {
    if (union_data[u] < 0) return u;
    return union_data[u] = find_rep(union_data[u], union_data);
}

void merge(int u, int v, vector<int> &union_data) {
    u = find_rep(u, union_data), v = find_rep(v, union_data);
    if (u == v) return;
    if (u < v) swap(u, v);
    union_data[u] += union_data[v];
    union_data[v] = u;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, e, p; cin >> n >> e >> p;
    vector<pair<double, double>> location(n);
    for (int i= 0; i<n; i++) cin >> location[i].first >> location[i].second;
    vector<int> union_data(n+1, -1);
    for (int i= 0; i<e; i++) merge(n, i, union_data);
    for (int i= 0; i<p; i++) {
        int a,b; cin >> a >> b;
        a--, b--;
        merge(a, b, union_data);
    }
    vector<pair<double, pair<int, int>>> edge;
    for (int i= 0; i<n; i++) {
        for (int j = i+1; j<n; j++) {
            int rep_i = find_rep(i, union_data), rep_j = find_rep(j, union_data);
            if (rep_i == rep_j) continue;
            double dist = pow(location[i].first - location[j].first, 2) + pow(location[i].second - location[j].second, 2);
            dist = sqrt(dist);
            edge.push_back(make_pair(dist, make_pair(i, j)));
        }
    }
    sort(edge.begin(), edge.end(), [](pair<double, pair<int, int>> a, pair<double, pair<int, int>> b) {
        return a.first > b.first;
    });
    int curr_max = 0;
    double ret = 0;
    for (int i= 0; i<=n; i++) {
        if (union_data[i] < 0) curr_max = max(curr_max, -union_data[i]);
    }
    while (!edge.empty() && curr_max != n+1) {
        pair<double, pair<int, int>> curr = edge.back();
        edge.pop_back();
        int u = curr.second.first, v = curr.second.second;
        int rep_u = find_rep(u, union_data), rep_v = find_rep(v, union_data);
        if (rep_u == rep_v) continue;
        merge(u, v, union_data);
        ret += curr.first;
        rep_u = find_rep(u, union_data), rep_v = find_rep(v, union_data);
        if (union_data[rep_u] < 0) curr_max = max(curr_max, -union_data[rep_u]);
        if (union_data[rep_v] < 0) curr_max = max(curr_max, -union_data[rep_v]);
    }
    printDecimal(7) << ret << '\n'; 
} 
