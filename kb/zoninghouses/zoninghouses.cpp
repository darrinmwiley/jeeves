/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/zoninghouses
TAGS: segment tree (beats?)
EXPLANATION:
- This problem can be solved using a special kind of Segment Tree, in which each node will keep track of the 
following information:
    + fmax - largest value in the current range
    + smax - largest value that is strictly smaller than fmax (second_max)
    + cnt_fmax - number of occurrences of fmax in the current range
    + fmax_pos - index of occurrence of fmax in the current range

    + fmin - smallest value in the current range
    + smin - smallest value that is strictly larger than fmin (second_min)
    + cnt_fmin - number of occurrences of fmin in the current range
    + fmin_pos - index of occurrence of fmin in the current range
 
 - Create 2 of such segment trees, one for x coordinates, one for y coordinates
 - Build the 2 trees based on the coordinates of the houses

 - For each query:
    + It can be seen that all the houses included in the range will be within the 
    square with side of length max(x_tree.fmax - x_tree.fmin, y_tree.fmax - y_tree.fmin)
    + It can be seen if there is only 1 house with x_tree.fmax as x coordinate, then the square may be able
    to shrink to max(x_tree.smax - x_tree.fmin, y_tree.fmax - y_tree.fmin)
        + If the removed house happens to be the only house that has its y-coordinates as y_tree.fmax or y_tree.fmin
        then we can further shrink the square to either max(x_tree.smax - x_tree.fmin, y_tree.smax - y_tree.fmin) or 
        max(x_tree.smax - x_tree.fmin, y_tree.fmax - y_tree.smin) respectively
        + Otherwise, the square will be max(x_tree.smax - x_tree.fmin, y_tree.fmax - y_tree.fmin)
    + Same observation can be applied if there is only one 1 house with x_tree.fmin as x coordinates
    + Remember to check the case in which only the y bounds can be shrinked
     

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
class SegmentTree {
   public:
    SegmentTree(int n, T b, function<T(T, T)> f) {
        arr_sz = n;
        base = b;
        eval = f;
        int sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        tree.assign(sz * 2 + 1, T{});
    }
    void set(int i, T x) {
        set(0, 0, arr_sz - 1, i, x);
    }
    T query(int l, int r) {
        return query(0, 0, arr_sz - 1, l, r);
    }

   private:
    vec<T> tree;
    int arr_sz;
    function<T(T, T)> eval;
    T base;

    void set(int curr_idx, int curr_l, int curr_r, int i, T x) {
        assert(curr_l <= curr_r);
        if (curr_l == curr_r) {
            tree[curr_idx] = x;
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid)
            set(curr_idx * 2 + 1, curr_l, mid, i, x);
        else
            set(curr_idx * 2 + 2, mid + 1, curr_r, i, x);
        tree[curr_idx] = eval(tree[curr_idx * 2 + 1], tree[curr_idx * 2 + 2]);
    }

    T query(int curr_idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || curr_l > r || curr_r < l) return base;
        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) return tree[curr_idx];
        int mid = curr_l + (curr_r - curr_l) / 2;
        T left = query(curr_idx * 2 + 1, curr_l, mid, l, r);
        T right = query(curr_idx * 2 + 2, mid + 1, curr_r, l, r);
        return eval(left, right);
    }
};

struct Beats {
    int fmax, fmin;
    int smax, smin;
    int cnt_fmax, cnt_fmin;
    int fmax_pos, fmin_pos;
    Beats() = default;
    Beats(int pos, int low, int high) : fmax{low}, fmin{high}, smax{low}, smin{high}, cnt_fmax{0}, cnt_fmin{0}, fmax_pos{pos}, fmin_pos{pos} {}
    explicit Beats(int pos, int v) : fmax{v}, fmin{v}, smax{-iinf}, smin{iinf}, cnt_fmax{1}, cnt_fmin{1}, fmax_pos{pos}, fmin_pos{pos} {}
    Beats operator+(Beats other) {
        Beats fin;
        if (fmax < other.fmax) {
            fin.fmax = other.fmax;
            fin.fmax_pos = other.fmax_pos;
            fin.cnt_fmax = other.cnt_fmax;
            fin.smax = max(fmax, other.smax);
        } else if (fmax > other.fmax) {
            fin.fmax = fmax;
            fin.fmax_pos = fmax_pos;
            fin.cnt_fmax = cnt_fmax;
            fin.smax = max(other.fmax, smax);
        } else {
            fin.fmax = fmax;
            fin.fmax_pos = fmax_pos;
            fin.cnt_fmax = cnt_fmax + other.cnt_fmax;
            fin.smax = max(other.smax, smax);
        }

        if (fmin < other.fmin) {
            fin.fmin = fmin;
            fin.fmin_pos = fmin_pos;
            fin.cnt_fmin = cnt_fmin;
            fin.smin = min(other.fmin, smin);
        } else if (fmin > other.fmin) {
            fin.fmin = other.fmin;
            fin.fmin_pos = other.fmin_pos;
            fin.cnt_fmin = other.cnt_fmin;
            fin.smin = min(fmin, other.smin);
        } else {
            fin.fmin = fmin;
            fin.fmin_pos = fmin_pos;
            fin.cnt_fmin = cnt_fmin + other.cnt_fmin;
            fin.smin = min(smin, other.smin);
        }
        return fin;
    }
};

void prayGod() {
    int n;
    cin >> n;
    int q;
    cin >> q;

    vec<pair<int, int>> houses(n);
    cin >> houses;

    SegmentTree<Beats> xtree(n, Beats(-1, -iinf, iinf), [](Beats a, Beats b) {
        return a + b;
    });

    SegmentTree<Beats> ytree(n, Beats(-1, -iinf, iinf), [](Beats a, Beats b) {
        return a + b;
    });

    for (int i = 0; i < n; i++) {
        xtree.set(i, Beats(i, houses[i].first));
        ytree.set(i, Beats(i, houses[i].second));
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        Beats curr_x = xtree.query(--l, --r);
        Beats curr_y = ytree.query(l, r);

        int ret = max(curr_x.fmax - curr_x.fmin, curr_y.fmax - curr_y.fmin);

        if (curr_x.cnt_fmin == 1) {
            int x_bound = curr_x.fmax - curr_x.smin;
            int y_bound = curr_y.fmax - curr_y.fmin;
            if (curr_y.cnt_fmin == 1 && curr_y.fmin_pos == curr_x.fmin_pos) {
                y_bound = curr_y.fmax - curr_y.smin;
            } else if (curr_y.cnt_fmax == 1 && curr_y.fmax_pos == curr_x.fmin_pos) {
                y_bound = curr_y.smax - curr_y.fmin;
            }
            ret = min(ret, max(x_bound, y_bound));
        }

        if (curr_x.cnt_fmax == 1) {
            int x_bound = curr_x.smax - curr_x.fmin;
            int y_bound = curr_y.fmax - curr_y.fmin;
            if (curr_y.cnt_fmin == 1 && curr_y.fmin_pos == curr_x.fmax_pos) {
                y_bound = curr_y.fmax - curr_y.smin;
            } else if (curr_y.cnt_fmax == 1 && curr_y.fmax_pos == curr_x.fmax_pos) {
                y_bound = curr_y.smax - curr_y.fmin;
            }
            ret = min(ret, max(x_bound, y_bound));
        }

        if (curr_y.cnt_fmin == 1) {
            int y_bound = curr_y.fmax - curr_y.smin;
            int x_bound = curr_x.fmax - curr_x.fmin;
            if (curr_x.cnt_fmin == 1 && curr_x.fmin_pos == curr_y.fmin_pos) {
                x_bound = curr_x.fmax - curr_x.smin;
            } else if (curr_x.cnt_fmax == 1 && curr_x.fmax_pos == curr_x.fmin_pos) {
                x_bound = curr_x.smax - curr_x.fmin;
            }
            ret = min(ret, max(x_bound, y_bound));
        }

        if (curr_y.cnt_fmax == 1) {
            int y_bound = curr_y.smax - curr_y.fmin;
            int x_bound = curr_x.fmax - curr_x.fmin;
            if (curr_x.cnt_fmin == 1 && curr_x.fmin_pos == curr_y.fmax_pos) {
                x_bound = curr_x.fmax - curr_x.smin;
            } else if (curr_x.cnt_fmax == 1 && curr_x.fmax_pos == curr_y.fmax_pos) {
                x_bound = curr_x.smax - curr_x.fmin;
            }
            ret = min(ret, max(x_bound, y_bound));
        }

        cout << ret << '\n';
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
