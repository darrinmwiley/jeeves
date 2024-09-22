/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/leftandright
TAGS: implementation
EXPLANATION:
- Since the robot has to move to the right to reach the first house => we can add an 'R' at the front of the string
- Create an array that will store the result
- Split the string into substrings starting with an R, followed by (x) amount of L (x >= 0)
- e.g: R (x = 0), RLL (x = 2), RLLLLLL (x = 6)
- Create a variable called curr => set it to 0
- For each substring resulted from previous step, let the current substring be s[i..j] (0-indexed, i = index in original string of first letter in substring):
  + result[i] = curr + j-1+1
  + curr = result[i] 
- For each value in result array, 
  + If result[i] is not initialized, result[i] = result[i-1] - 1
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
void printArray(vector<T> arr) { for (int i = 0; i<size(arr); i++) {cout << arr[i] << '\n';} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T> 
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    s = "R" + s;
    vector<int> ret(n, -1), idx;
    for (int i= n-1; i>=0; i--) {
        if (s[i] == 'R') idx.push_back(i);
    }
    reverse(idx.begin(), idx.end());
    for (int i= 0; i<size(idx)-1; i++) {
        ret[idx[i]] = idx[i+1];
    }
    ret[idx.back()] = n;
    for (int i = 1; i<n; i++) {
        if (ret[i] == -1) ret[i] = ret[i-1] -1;
    }
    printArray(ret);
    
}  
