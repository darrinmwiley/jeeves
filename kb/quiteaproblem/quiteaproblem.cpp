/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/quiteaproblem
TAGS: implementation
EXPLANATION:
- Check each substring to see if it is "problem"
- Edge cases: 
    - There could be whitespace between paragraphs => print "no" if such line exists
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "yes": "no") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265
 
//const ll inf = 0x3f3f3f3f;
const int inf = 1e9 + 10;
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

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s; 
    int space_cnt = 0;
    while (getline(cin, s)) {
        if (s == "") {
            space_cnt++;
            if (space_cnt >= 2) break;
            continue;
        }
        if (space_cnt == 1) cout << "no" << '\n';
        space_cnt = 0;
        bool exists = false;
        for (int i= 0; i<=len(s)-7 && !exists; i++) {
            string curr = s.substr(i, 7);
            for (int j= 0; j<7; j++) curr[j] = char(tolower(curr[j]));
            if (curr == "problem") exists = true;
        }
        printVerdict(exists);
    }
} 
