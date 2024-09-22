/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/socialadvertising
TAGS: bitmask, brute-force
EXPLANATION:
- Scan through all possible combinations of people using bitmasks
  + If a person is included in the mask, mark that person and their friends as seen the ad
  + The final result will be minimum number of people included in the mask for all masks in which everyone can see the ad
- Time complexity for the above solution will be O(t*n*(2^n)) (n is number of friends, and t is number of test cases)
=> Max number of operations will be 10*20*(2^20) = 209,715,200 operations (which is possible in 1 second)
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
#define debugDecimal(d) cerr << setprecision(d) << fixed
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265
 
const int iinf = 0x3f3f3f3f;
const ll inf = 1e18;
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
 
 
const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

 
void prayGod() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<vector<int>> graph(n);
        for (int i = 0; i<n; i++) {
            int friendlist; cin >> friendlist;
            for (int j =0 ; j<friendlist; j++) {
                int neighbor; cin >> neighbor;
                graph[i].push_back(neighbor-1);
            }
        }

        int ret = 1e9;
        
        // Scan through all possible masks
        for (int mask = 1; mask<(1<<n); mask++) {
            vector<bool> visited(n, false);
            for (int i = 0; i<n; i++) {
                if (mask & (1<<i)) {
                    // If a person is included in the mask, mark them and their friends as seen the ad
                    visited[i] = true;
                    for (int neighbor : graph[i]) visited[neighbor] = true;
                }
            }
            // Check if everyone sees the ad
            bool possible = true;
            for (int i = 0; i<n && possible; i++) {
                if (!visited[i]) possible = false;
            }

            // If everyone see the ad, update final answer
            if (possible) ret = min(ret, __builtin_popcount(mask));
        }

        cout << ret << '\n';
    }
}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("input.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / 1000.0;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " ms" << '\n';
} 
