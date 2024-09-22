/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/gcds
TAGS: math, number theory
EXPLANATION:
Key observation: 
    - Since a <= 100, we can say that there are only at most 100 possible candidates for GCD
Approach:
    - For every possible candidate of GCD (let's call it x), count the number of subarray that has x as GCD 
    (we will store it in cnt[x])
        + Create a new array (I call it curr in this submission), in which arr[i] = a[i] % x
        + Use 2-pointers approach to find all segments of "arr" such that all elements in the segment is 0
            + E.g: if arr = [0, 1, 2, 3, 0, 0, 0, 1, 2, 0, 0, 0]
            + We can see that there are 1 segment of length 1 and 2 segments of length 3
            + Given the length of the segment as sz, then the number of subarray that we can create out of that segments
            is (sz)(sz + 1) / 2 
    - Note, if a[i] is divisible by multiple of x, then a[i] is also divisible by x, meaning that some invalid subarray
    will be counted as well (because their gcd is multiple of x, not x)
    - This is resolved by subtracting sum(cnt[y]) from cnt[x], where y is all multiples of x
    - The final answer will be the number of elements in cnt that is greater than 0
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
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

const int iinf = 0x3f3f3f3f;
const ll inf = 1000000000000000010;
const ll mod = 1e9 + 7;

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string ccurr = "";                     \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ') continue;       \
            if (_s[zz] == ',') {               \
                _ss << ' ' + ccurr;            \
                ccurr = "";                    \
            } else                             \
                ccurr += _s[zz];               \
        }                                      \
        _ss << ' ' + ccurr;                    \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) { cerr << '\n'; }
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args) {
    cerr << " [" << *it << ": " << a << "] ";
    vars(++it, args...);
}

#define printVerdict(verdict) \
    cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) \
    cout << setprecision(d) << fixed
#define printCase(_) \
    cout << "Case #" << (_) << ": "

template <class T1, class T2, class T3>
void printTuple(const tuple<T1, T2, T3> &t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) { return out << p.first << " " << p.second; }
template <class T>
ostream &operator<<(ostream &out, const vector<T> &arr) {
    for (const T &a : arr) out << a << " ";
    return out;
}
template <class T>
ostream &operator<<(ostream &out, const vector<vector<T>> &grid) {
    for (const vector<T> &row : grid) out << row << '\n';
    return out;
}
template <class T>
istream &operator>>(istream &in, vector<T> &arr) {
    for (T &a : arr) in >> a;
    return in;
}
template <class T>
void readIdx(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <class T1, class T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    in >> a.first >> a.second;
    return in;
}

// Error handling for out of bounds
template <class T>
class vec : public std::vector<T> {
   public:
    using std::vector<T>::vector;
    T &operator[](int i) {
        return std::vector<T>::at(i);
    }
    const T &operator[](int i) const {
        return std::vector<T>::at(i);
    }
};

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

void prayGod() {
    int n;
    cin >> n;
    vec<int> a(n);
    cin >> a;

    vec<int> dp(101);

    for (int g = 100; g >= 1; g--) {
        vec<int> curr(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            curr[i] %= g;
        }
        int ptr = 0;
        for (int i = 0; i < n; i++) {
            if (curr[i] != 0 && curr[ptr] == 0) {
                int sz = i - ptr;
                dp[g] += sz * (sz + 1) / 2;
                ptr = i;
            } else if (curr[i] == 0 && curr[ptr] != 0) {
                ptr = i;
            }
        }
        if (curr[ptr] == 0) dp[g] += (n - ptr) * (n - ptr + 1) / 2;
        for (int mul_g = g * 2; mul_g <= 100; mul_g += g) {
            dp[g] -= dp[mul_g];
        }
    }

    int ret = 0;
    for (int i = 0; i <= 100; i++) {
        ret += (dp[i] > 0);
    }

    cout << ret << '\n';
}

int main() {
    clock_t start = clock();

    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    if (EXTERNAL_INPUT)
        freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT)
        freopen(OUTPUT_FILE, "w", stdout);

    prayGod();

    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME)
        debugDecimal(5) << time_taken << " s" << '\n';
}
