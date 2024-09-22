/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/dancerecital
TAGS: brute-force
EXPLANATION:
 - Check through all possible permutation of the routines (all n! permutations) and keep track the number of quick change necessary
 => With some pre-computation, the above can be done in O(n*(n!)), which is possible for n <= 10
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
    // I/O
    int n; cin >> n;
    vector<pair<string, int>> routine(n);
    for (int i = 0; i<n; i++) {
        cin >> routine[i].first;
        routine[i].second = i;
    }

    // Sort the routine list for next_permutation
    sort(routine.begin(), routine.end(), [&](pair<string, int> a, pair<string, int> b) {
        return a.first < b.first;
    });

    // Pre-compute the frequency of every letter for each routine
    vector<vector<int>> cnt(n, vector<int>(26, 0));
    for (int i = 0; i<n; i++) {
        for (char c : routine[i].first) cnt[i][c-'A']++;
    }
    
    // relation[i][j] denotes the number of quick changes necessary to go from routine[i] to routine[j]
    vector<vector<int>> relation(n, vector<int>(n, 0));
    for (int i = 0; i<n; i++) {
        for (int j = i+1; j<n; j++) {
            int currCnt = 0;
            for (char c : routine[j].first) currCnt += cnt[i][c-'A'] > 0;
            relation[i][j] = relation[j][i] = currCnt;
        }
    }

    int ret = 1e9;

    // Check through all possible permutations of routine using next_permutation
    do {
        int quick_change = 0;
        for (int i = 1; i<n; i++) quick_change += relation[routine[i-1].second][routine[i].second];

        // Update the result accordingly
        ret = min(ret, quick_change);
    } while (next_permutation(routine.begin(), routine.end(), [&](pair<string, int> a, pair<string, int> b) {
        return a.first < b.first;
    }));
    
    cout << ret << '\n';
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
