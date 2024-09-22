/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/tank
TAGS: binary search, shoelace theorem
EXPLANATION:
- Binary search through all possible height of the water, for each candidate: 
   + Draw a line y = candidate through the polygon
   + Compute the area of the polygon created by the points below or intersect the line drew in step 1 using the Shoelace Theorem
   + The volume for water at a given height can be computed from the area, the height, and the given depth
   + The final result will be the height that resulted in the volume closest to the given amount of litters 
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
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265
 
//const int inf = 0x3f3f3f3f;
const ll inf = 1e15;
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

#define prayGod main

int prayGod() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; double d,l; cin >> n >> d >> l;
    vector<pair<int, int>> point(n);
    int miny = 1001, maxy = -1001;
    for (int i = 0; i<n; i++) {
        readPair(point[i]);
        miny = min(miny, point[i].second), maxy = max(maxy, point[i].second);
    }

    // Find intersection between the polygon and the guess-line
    function<pair<double, double>(pair<int, int>, pair<int, int>, double)> find_mid = [&](pair<int, int> a, pair<int, int> b, double target) {
        double delta_x = double(a.first - b.first), delta_y = double(a.second - b.second);
        if (fabs(delta_x) == 0) return make_pair(double(a.first), target);
        double slope = delta_y / delta_x;
        double b_const = a.second - slope*a.first;
        pair<double, double> ret = make_pair((target-b_const)/slope, target);
        return ret;
    };

    // Compute the resulted sub-polygon after drawing "guess-line"
    function<double(double)> area = [&](double guess_line) {
        vector<pair<double, double>> valid;
        for (int i = 0; i<n; i++) {
            if (point[i].second == guess_line || (point[i].second < guess_line && point[(i+1)%n].second <= guess_line)) {
                valid.emplace_back(double(point[i].first), double(point[i].second));
            }
            else if (point[i].second < guess_line && point[(i+1)%n].second > guess_line) {
                valid.emplace_back(double(point[i].first), double(point[i].second));
                valid.push_back(find_mid(point[i], point[(i+1)%n], guess_line));
            }
            else if (point[i].second > guess_line && point[(i+1)%n].second < guess_line) {
                valid.push_back(find_mid(point[i], point[(i+1)%n], guess_line));
            }
        }
        double ret = 0.0;
        for (int i = 0; i<len(valid); i++) {
            ret += valid[i].first * valid[(i+1)%len(valid)].second - valid[(i+1)%len(valid)].first * valid[i].second;
        }
        return ret*0.5;
    };
    
    // Search for height that resulted in the largest volume that is smaller than or equal given L
    int low = miny*1e2, high = maxy*1e2;
    double ret_left = -1, curr_left = -1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        double curr = area(double(mid) * (1e-2)) * d * 1e-3;
        if (curr <= l) ret_left = double(mid)*(1e-2), low = mid+1, curr_left = curr;
        else high = mid-1;
    }

    // Search for height that resulted in the smallest volume that is larger than or equal given L
    low = miny*1e2, high = maxy*1e2;
    double ret_right = -1, curr_right = -1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        double curr = area(double(mid) * (1e-2)) * d * 1e-3;
        if (curr >= l) ret_right = double(mid)*(1e-2), high = mid-1, curr_right = curr;
        else low = mid+1;
    }

    // Take the one that is closer to L
    if (fabs(curr_right - l) < fabs(curr_left - l)) {
        assert(ret_right != -1);
        printDecimal(2) << ret_right << '\n';
    }
    else {
        assert(ret_left != -1);
        printDecimal(2) << ret_left << '\n';
    }
} 

