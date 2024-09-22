/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/landscape
TAGS: segment tree, range update
EXPLANATION:
- A simpler problem 
    + Consider this version of the problem, in which one will only either raise or depress
    => It can be seen that this easier version can be solved using a data structure called Difference Array 
       (https://www.geeksforgeeks.org/difference-array-range-update-query-o1/)
- Observation to solve the original problem:
    + Let diff be the difference array of the array arr
    => It can be seen that adding x to all elements in diff[l:r+1] is arr is equivalent to 
    adding x to arr[l], x*2 to arr[l + 1], x * 3 to arr[l + 2],..., and x * (r - l + 1) to all element from arr[r] afterward
- Final solution
    + If the operation is either raise or depress: 
        Then add 1 to diff[x1] and subtract 1 from diff[x2 + 1]
    + If the operation is either hill or valley
        Let sz the length of update range
        If sz is even:
            It can be seen that we need to add 1 to all elements in diff[x1 : x1 + sz/2 - 1] (the first sz / 2 elements in the update range)
            After that, we will need to subtract 1 from all elements in diff[x1 + sz / 2 + 1 : x2] (the rest of the elements except diff[x1 + mid/2])
            Assume that (without loss of generality) sz is 4, we will have the following arrays as delta to each element:
                hill_delta[x1:x2 + 1] = [1, 1, 0, -1]
                valley_delta[x1:x2 + 1] = [-1, -1, 0, 1]
        If sz is odd:
            It can be seen that we need to add 1 to all elements in diff[x1 : x1 + sz/2] (the first ceil(sz / 2) elements in the update range)
            After that, we will need to subtract 1 from all elements in diff[x1 + sz / 2 + 1 : x2] (the rest of the elements)
            Assume that (without loss of generality) sz is 7, we will have the following arrays as delta to each element:
                hill_delta[x1:x2 + 1] = [1, 1, 1, 1, -1, -1, -1]
                valley_delta[x1:x2 + 1] = [-1, -1, -1, -1, 1, 1, 1]
    + It can be seen that by using segment tree with lazy propagation, it is possible to create hill / valey with just 2 O(log(n)) call
    + The final height of the position will be the prefix sum of the different array
    + Final time complexity: O((n + k)*log(n))
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

template <class T>
struct SegmentTree {
    T base_val;
    int arr_size;
    vector<T> tree, lazy;

    SegmentTree(int n) {
        base_val = 0, arr_size = n;
        int size = 1;
        while (size < n) size *= 2;
        size = 2 * size + 1;
        tree.assign(size, 0);
        lazy.assign(size, 0);
    };

    T eval(T a, T b) { return a + b; }

    void propagate(int idx, int curr_l, int curr_r) {
        if (lazy[idx]) {
            tree[idx] += (curr_r - curr_l + 1) * lazy[idx];

            if (curr_l != curr_r) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }

            lazy[idx] = 0;
        }
    }

    void update(int idx, int curr_l, int curr_r, int l, int r, T val) {
        if (curr_l > curr_r) return;

        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return;

        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) {
            tree[idx] += (curr_r - curr_l + 1) * val;
            if (2 * idx + 1 < len(lazy)) lazy[2 * idx + 1] += val;
            if (2 * idx + 2 < len(lazy)) lazy[2 * idx + 2] += val;
            return;
        }

        int mid = curr_l + (curr_r - curr_l) / 2;
        update(idx * 2 + 1, curr_l, mid, l, r, val);
        update(idx * 2 + 2, mid + 1, curr_r, l, r, val);
        tree[idx] = eval(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    T query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r) return base_val;

        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return base_val;

        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) return tree[idx];

        int mid = curr_l + (curr_r - curr_l) / 2;
        T left = query(idx * 2 + 1, curr_l, mid, l, r), right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        return eval(left, right);
    }

    void update(int l, int r, T val) { update(0, 0, arr_size - 1, l, r, val); }
    T query(int l, int r) { return query(0, 0, arr_size - 1, l, r); }
};

void prayGod() {
    int n, k;
    cin >> n >> k;
    SegmentTree<ll> tree(n + 1);

    for (int i = 0; i < k; i++) {
        char op;
        int x1, x2;
        cin >> op >> x1 >> x2;
        x1--, x2--;
        switch (op) {
            case 'H': {
                int sz = (x2 - x1 + 1);
                int midpoint = x1 + sz / 2;
                tree.update(x1, midpoint - ((sz % 2) ^ 1), 1);
                tree.update(midpoint + 1, x2 + 1, -1);
                break;
            }
            case 'D': {
                tree.update(x1, x1, -1);
                tree.update(x2 + 1, x2 + 1, 1);
                break;
            }
            case 'R': {
                tree.update(x1, x1, 1);
                tree.update(x2 + 1, x2 + 1, -1);
                break;
            }
            case 'V': {
                int sz = (x2 - x1 + 1);
                int midpoint = x1 + sz / 2;
                tree.update(x1, midpoint - ((sz % 2) ^ 1), -1);
                tree.update(midpoint + 1, x2 + 1, 1);
                break;
            }
            default: {
                assert(false);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << tree.query(0, i) << '\n';
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
