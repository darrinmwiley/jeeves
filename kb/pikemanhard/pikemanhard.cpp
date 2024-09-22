/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/pikemanhard
TAGS: binary search, sorting, math
EXPLANATION:
- Observation #1: Since t[i] is computed by taking an arbitrary number % c, it is possible to say t[i] will never exceeds c and that the sequence of t 
will eventually repeat at some point
- Observation #2: The penalty value can be minimized by prioritizing problems that require less time
- Approach: 
    + Compute t[i] until either there are n elements or a repeat is found (refer to Observation #1)
    + Binary search the number of problems that can be solved
       + For every mid: 
         + Categorize the problems based on the time it requires, and compute the number of each element in each category
         + Sort the categories based on the time required in ascending order (Refer to Observation #2)
         + The total time needed to solved all problems from first category to i-th category can be computed using prefix sum as follow: 
                + totalTime[i] = totalTime[i-1] + time[i]*(# of element in i-th element)
         + The penalty of all problems from the first category to the i-th category can be computed as follow: 
                + (penalty[i] = penalty[i-1] + time[i] * (1 + 2 + ... + # of element in i-th group) + totalTime[i-1] * (# of elements in i-th group)) % (1e9 + 7)
         + If totalTime[lastCategory] <= t, update max number of problems and the penalty, and move the bound up
         + Else move the bound down
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

ll mult(ll a, ll b, ll m = mod) { return (a%m * b%m)%m; }

void prayGod() {
    // inv2 = 2^(-1) modulo (1e9 + 7)
    const ll inv2 = 500000004;
    ll n,t,a,b,c,t0; cin >> n >> t >> a >> b >> c >> t0;
    ll curr = t0, repeatVal = -1;
    int repeatedIdx = -1;

    set<ll> seen;
    vector<ll> possible;

    while (!present(seen, curr) && len(seen) < n) {
        seen.insert(curr);
        possible.push_back(curr);
        curr = (curr*a + b)%c + 1;
        if (present(seen, curr)) repeatVal = curr;
    }

    int arrSize = len(possible);
    for (int i = 0; i<arrSize; i++) {
        if (possible[i] == repeatVal) repeatedIdx = i;
    }

    ll maxSolved = 0, finalPenalty = 0;
    ll low = 1, high = n;
    
    // summation(val) % mod = ( val*(val+1)/2 ) % mod = (val*(val+1)*2^(-1))%mod
    function<ll(ll)> summation = [&](ll val) { return (mult(val+1, val) * inv2) % mod; };
    
    // Worst-case complexity: c*log(c)*log(n)
    while (low <= high) {
        ll mid = low + (high - low)/2;
        vector<pair<ll, ll>> currWeight;
        for (int i = 0; i<arrSize; i++) {
            if (ll(len(currWeight)) >= mid) break;
            currWeight.emplace_back(possible[i], 1);
        }

        if (mid > arrSize) {
            ll repeatCnt = (mid - arrSize) / (arrSize - repeatedIdx), remain = (mid - arrSize) % (arrSize - repeatedIdx);
            for (int i = repeatedIdx; i < arrSize; i++) {
                currWeight[i].second += repeatCnt;
                if (i < repeatedIdx + remain) currWeight[i].second++;
            }
        }

        ll penalty = 0, totalTime = 0;
        bool validMid = true;
        
        sort(currWeight.begin(), currWeight.end());
        for (int i = 0; i<len(currWeight); i++) {
            if (t - totalTime < currWeight[i].first * currWeight[i].second) {
                validMid = false;
                break;
            }
            penalty = (penalty + mult(currWeight[i].first, summation(currWeight[i].second))) % mod;
            penalty = (penalty + mult(totalTime, currWeight[i].second)) % mod;
            totalTime += currWeight[i].first * currWeight[i].second;
        }

        if (validMid) maxSolved = mid, finalPenalty = penalty, low = mid+1;
        else high = mid-1;
    }

    cout << maxSolved << " " << finalPenalty << '\n';
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

