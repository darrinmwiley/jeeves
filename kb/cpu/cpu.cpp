/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/cpu
TAGS: bruteforce
EXPLANATION:
- Key observation:
    + There are only more or less 200 possible explosive number within the given range
    + It is possible to generate all possible explosive numbers within given range without getting TLE
- Approach:
    + Generate all possible explosive numbers and store all of them in an array (in sorted order) 
    + For each query, the low and upper bound can be found using binary search
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

bool is_prime(int v) {
    if (v < 2) return false;
    for (int d = 2; d * d <= v; d++) {
        if (v % d == 0) return false;
    }
    return true;
}

void prayGod() {
    // Use set to prevent duplicates and maintain order
    set<ll> all_explosive;

    // Iterate through all possible pairs of a and b
    for (int a = -1000; a <= 1000; a++) {
        for (int b = -1000; b <= 1000; b++) {
            // total will store cumulative product of all primes generated thus far
            // curr will store current prime
            ll total = 1, curr = 1, k = 1;
            // Assume that 100 factors is enough to cover all necessary values
            for (; k <= 100; k++) {
                // If total exceeds 2e9, then no need to compute as value is out of bounds
                if (total > 2e9) break;
                int prev = curr;

                // Generate new number
                curr = curr * a + b;

                // If new number is not prime or is the same as previous number, then it is no longer possible
                // to generate valid number with current (a, b) pair
                if (!is_prime(curr) || prev == curr) {
                    k = -1;
                    break;
                }

                // Apply current number to cumulative product
                total *= curr;

                // A number can only be considered explosive if there are at least 3 factors and within right range
                if (k >= 3 && total >= 0 && total <= 2e9) all_explosive.insert(total);
            }
            // A number can only be considered explosive if there are at least 3 factors and within right range
            if (k >= 3 && total >= 0 && total <= 2e9) all_explosive.insert(total);
        }
    }

    // Store all explosives numbers in an array for binary search
    vec<ll> temp(all_explosive.begin(), all_explosive.end());

    int n;
    cin >> n;

    // Process query
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int left = lower_bound(temp.begin(), temp.end(), a) - temp.begin();
        int right = upper_bound(temp.begin(), temp.end(), b) - temp.begin() - 1;
        cout << right - left + 1 << '\n';
    }
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
