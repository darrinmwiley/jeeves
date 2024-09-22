/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/landline
TAGS: mst, dsu
EXPLANATION:
- Observation #1: if the system is represented as a tree, then all insecure buildings has to be leaves of that tree
=> Approach: 
- Build MST from secure buildings
- For each insecure buildings, connect it with the closest secure building (if any)
- If all buildings are not connected in the end, then the result will be "impossible"
- Else, the result will be the total cost

* Some edge cases to consider: 
- n = 1 => distance is 0 regardless of secure status
- n = 2 => if there is a direct between the 2 nodes, it is possible to make such connections (regardless whether they are secure or not)
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
    union_data[u] = find_rep(union_data[u], union_data);
    return union_data[u];
}

void merge(int u, int v, vector<int> &union_data, int &ret, int dist) {
    u = find_rep(u, union_data), v= find_rep(v, union_data);
    if (u == v) return;
    ret += dist;
    if (union_data[u] > union_data[v]) swap(u, v);
    union_data[u] += union_data[v];
    union_data[v] = u;
}

string solve() {
    int n,m,p; cin >> n >> m >> p;
    set<int> insecure;
    for (int i= 0; i<p; i++) {
        int temp; cin >> temp;
        temp--;
        insecure.insert(temp);
    }
    vector<pair<int, pair<int, int>>> secure_edge;
    vector<vector<pair<int, int>>> insecure_graph(n);

    int ret = 0;
    bool possible = true, finished = false;

    for (int i= 0; i<m; i++) {
        int u, v, dist; cin >> u >> v >> dist;
        u--, v--;
        if (present(insecure, u) || present(insecure, v)) {
            insecure_graph[u].emplace_back(v, dist);
            insecure_graph[v].emplace_back(u, dist);
        }
        else secure_edge.push_back(make_pair(dist, make_pair(u, v)));
    }

    if (n == 1) return "0";

    sort(secure_edge.begin(), secure_edge.end());
    vector<int> union_data(n, -1);

    for (int i =0; i<len(secure_edge) && !finished; i++) {
        merge(secure_edge[i].second.first, secure_edge[i].second.second, union_data, ret, secure_edge[i].first);
        int rep = find_rep(secure_edge[i].second.first, union_data);
        if (-union_data[rep] == n) finished = true;
    }

    for (auto it = insecure.begin(); it != insecure.end() && !finished; it++) {
        int curr_node = *it;
        bool found = false;
        sort(insecure_graph[curr_node].begin(), insecure_graph[curr_node].end(), [](pair<int, int> a, pair<int, int> b) {
            return a.second < b.second;
        });
        for (int i = 0; i<len(insecure_graph[curr_node]) && !found; i++) {
            if (!present(insecure, insecure_graph[curr_node][i].first) || n <= 2) {
                found = true;
                merge(curr_node, insecure_graph[curr_node][i].first, union_data, ret, insecure_graph[curr_node][i].second);
            }
        }
        if (!found) {
            possible = false;
            finished = true;
        }
    }

    int curr_max = 0;
    for (int i = 0; i<n; i++) {
        if (union_data[i] < 0) curr_max = max(curr_max, -union_data[i]);
    }

    if (curr_max != n) possible = false;

    if (!possible) return "impossible";
    return to_string(ret);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << solve() << '\n';
    
} 