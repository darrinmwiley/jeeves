/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/pagelayout
TAGS: backtracking
EXPLANATION:
- Represent the problem as a graph in which a vertex represents a story and an edge between 2 vertices means that 2 stories 
will overlap if both are included in the paper. Each vertex will have a value that corresponds to the story's area

=> Such representation boils the problem down to the following: 
  Given a graph, find a way to color some vertices such that no 2 colored vertices share the same edge and 
that the sum of values associated with the colored vertices is maximized 

=> It can be seen that this is a variant of the Graph Coloring problem, thus can be solved using backtracking  
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

struct Rectangle {
    pair<int, int> topLeft, bottomRight;
    int area;
    Rectangle() {
        topLeft = bottomRight = make_pair(-1, -1);
        area = 0;
    }
    Rectangle(int x, int y, int w, int h) {
        topLeft  = make_pair(x, y);
        bottomRight = make_pair(x+w, y+h);
        area = w*h;
    }
};
 
void prayGod() {
    int n; cin >> n;
    
    while (n) {
        vector<Rectangle> stories(n);
        for (int i = 0; i<n; i++) {
            int x,y,w,h; cin >> w >> h >> x >> y;
            stories[i] = Rectangle(x, y, w, h);
        }

        function<bool(int, int)> overlap = [&](int i, int j) {
            if (stories[i].bottomRight.first <= stories[j].topLeft.first || stories[i].topLeft.first >= stories[j].bottomRight.first) return false;
            if (stories[i].bottomRight.second <= stories[j].topLeft.second || stories[i].topLeft.second >= stories[j].bottomRight.second) return false;
            return true;
        };

        vector<vector<int>> graph(n);
        for (int i = 0; i<n; i++) {
            for (int j = i+1; j<n; j++) {
                if (overlap(i, j)) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        int currArea = 0, ret = 0;

        vector<bool> included(n, false);

        function<void(int)> solve = [&](int curr) {
            if (curr >= n) {
                ret = max(ret, currArea);
                return;
            }
            bool canInclude = true;
            for (int neighbor : graph[curr]) {
                if (included[neighbor]) {
                    canInclude = false;
                    break;
                }
            }
            if (canInclude) {
                included[curr] = true;
                currArea += stories[curr].area;
                solve(curr+1);
                included[curr] = false;
                currArea -= stories[curr].area;
            }
            solve(curr+1);
        };

        solve(0);

        cout << ret << '\n';
        cin >> n;
    }    

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