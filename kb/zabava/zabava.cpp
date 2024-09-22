/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/zabava
TAGS: dp, math
EXPLANATION:
* - Categorize each students based on the building that they will move in => resulted in m groups of students
* - For each of the m groups, it is possible to either do nothing or split the group into sub-groups such that every students in the same sub-group will leave the 
* building at the same time => the noise level of a subgroup will be summation from 1 to x (with x is the number of students in that sub-group)
* - Since only at most k operations is allowed, it is possible notice that we will need a total of at most m+k sub-groups (in case each building will have one 
* remaining group of students after all k operations are carried out) such that the sum of noise level in all sub-groups are minimized
* => This problem can be solved using DP Knapsack by keeping track of the number of large groups we have and the number of sub-groups we want to make.
* 
* Approach: 
*   + For each large group, compute the minimum noise level for all possible number of sub-groups that can be created from the current large group
*    => This can be done by distributing the students as evenly as possible among all the subgroup
*    e.g: If we want to split 5 students into 3 sub-groups, it is best to have the 2 sub-groups with size of 2 and the 1 sub-group with size of 1
* 
*   + Let dp[i][j] be the minimum noise level if there are i large groups and we want j sub-groups
*   => Recurrence relation:
*       + Let "list" be a list storing all possible number of sub-groups that can be splitted for the i-th large group 
*       + For each x in list:
*           dp[i][j] = min(dp[i][j], dp[i-1][j - x] + (minimum noise level when splitting the i-th large group into x sub-groups))
*   => Base case:
*       + dp[i][0] = infinity for all possible i (because it is impossible to split a group into 0 subgroups)
*       + dp[0][i] = (minimum noise level when splitting the first large group into i sub-groups) (i > 0)
*   => The final answer will be min(dp[m-1][i], 1 <= i <= m+k) 
* 
* Some details that may worth paying attention to: 
*   + If there are no students in a large group, the noise level will be 0 regardless of number of sub-groups we want to split into
*   + Summation from 1 to 100,000 exceeds int range, so long long should be used
* 
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
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
void printTuple(const tuple<T1, T2, T3> &t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(const pair<T1, T2> &p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(const vector<T> &arr) { for (int i = 0; i<len(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T> 
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }} 
template<class T>
void printGrid(const vector<vector<T>> &grid) {for (int i =0; i<len(grid); i++) {for (int j =0; j<len(grid[i]); j++) { cout << grid[i][j] << " ";}cout << '\n';}}
template<class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }
 
 
const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

void prayGod() {
    int n,m,k; cin >> n >> m >> k;
    vector<ll> event(n);
    read(event, n);
    
    vector<ll> cnt(m, 0);
    for (int e : event) cnt[e-1]++;
    
    function<ll(ll)> summation = [&](ll val) {
        return val*(val+1)/2;
    };
    
    // split[i][j] denotes min noise level when splitting the i-th large group into j sub-groups
    vector<vector<ll>> split(m, vector<ll>(m+k+1, inf));
    for (int i = 0; i<m; i++) {
        for (int j = 1; j<=m+k; j++) {
            if (!cnt[i]) split[i][j] = 0;
            else if (cnt[i] % j == 0) split[i][j] = summation(cnt[i]/j) * j;
            else {
                int rem = cnt[i] % j;
                split[i][j] = summation(cnt[i]/j + 1) * rem + summation(cnt[i]/j) * (j - rem);
            }
        }
    }
    
    
    vector<vector<ll>> dp(m, vector<ll>(m+k+1, inf));
    for (int i = 1; i<=m+k; i++) dp[0][i] = split[0][i];
    for (int i = 1; i<m; i++) {
        for (int j = 1; j<=m+k; j++) {
            for (int z = 1; z<=m+k; z++) {
                if (j >= z) dp[i][j] = min(dp[i][j], dp[i-1][j-z] + split[i][z]);
            }
        }
    }
    
    
    ll ret = inf;
    for (int i = 1; i<=m+k; i++) ret = min(ret, dp[m-1][i]);
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
