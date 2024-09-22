/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/primal
TAGS: binary search
EXPLANATION:
- Binary search the answer
- Let x be the current prime that is considered
  + Split the array in a way such that every sub-segments are >= x
  + If there are k segments, then x is obviously a possible answer
  + If there are less than k segments, then since k <= n, there is a way to split some sub-segments such that there will be k subsegments
  without changing the validity of the answer
  => x is also a possible answer
  + If there are more than k segments, then x cannot be the answer
  + Adjust the search space accordingly based on whether x is the answer
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
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
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
    int n,k; cin >> n >> k;
    vector<int> a(n); read(a, n);

    int max_val = 0;
    for (int val : a) max_val = max(max_val, val);

    vector<int> sieve(max_val + 1, -1);

    // If GCD of a segment is 1, then the score of that segment will be 0
    sieve[0] = sieve[1] = 0;

    vector<int> prime;

    // Compute largest prime divisor
    for (int i = 2; i <= max_val; i++) {
        if (sieve[i] == -1) {
            prime.push_back(i);
            for (int j = i; j<= max_val; j+=i) sieve[j] = i;
        }
    }

    // Binary search through the list of prime
    // Best is set to 0 in case no prime is possible
    int low = 0, high = len(prime)-1, best = 0;
    while (low <= high) {
        int mid = low + (high - low)/2;
        
        int seg_count = 1;
        int curr_gcd = a[0], curr_point = sieve[a[0]];
        
        for (int i = 1; i<n && seg_count < iinf; i++) {
            if (curr_point < prime[mid]) {
                seg_count = iinf;
                break;
            }
            curr_gcd = __gcd(curr_gcd, a[i]);
            curr_point = sieve[curr_gcd];

            // Create a new segment when it is no longer possible to expand the current one
            if (curr_point < prime[mid]) {
                seg_count++;
                curr_gcd = a[i];
                curr_point = sieve[a[i]];
            }
        }

        if (curr_point < prime[mid]) seg_count = iinf;

        // Adjust search space            
        if (seg_count > k) high = mid-1;
        else best = prime[mid], low = mid+1;
    }

    cout << best << '\n';

}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
} 
