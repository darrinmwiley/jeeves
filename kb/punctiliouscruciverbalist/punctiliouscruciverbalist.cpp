/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/punctiliouscruciverbalist
TAGS: implementation
EXPLANATION:
- Find all clues that need to be solved
- While there are still clues remaining
    + Traverse through the remaining clue, if the clue is solved, do nothing, else update its rank
    + Among all unsolved clues, find the next clue based on given criteria, "solve" it, and add it to answer list
- Print the answer list 
* Since the grid is 50x50 at most, the above solution will always be within the time limit
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

// Clue object
struct Clue {
    string direction;
    int clue_no;
    int row, col;
    int clue_size;
    double rank;
    bool solved;
    Clue(string dir, int no, int r, int c) {
        direction = dir;
        clue_no = no;
        row = r, col = c;
        clue_size = 0;
        rank = 0.0;
        solved = false;
    }
};

void H() {
    // I/O
    int r,c; cin >> r >> c;
    vector<vector<char>> grid(r, vector<char>(c));
    for (int i = 0; i<r; i++) {
        string s; cin >> s;
        for (int j = 0; j<c; j++) grid[i][j] = s[j];
    }

    // Find all available clues
    int curr_clue = 1;
    vector<Clue> clues;
    for (int i = 0; i<r; i++) {
        for (int j = 0; j<c; j++) {
            if (grid[i][j] == '#') continue;
            bool has_clue = false;
            if (!inrange(i-1, 0, r-1) || grid[i-1][j] == '#') {
                has_clue = true;
                clues.emplace_back("D", curr_clue, i, j);
            } 
            if (!inrange(j-1, 0, c-1) || grid[i][j-1] == '#') {
                has_clue = true;
                clues.emplace_back("A", curr_clue, i, j);
            }
            if (has_clue) curr_clue++;
        }
    }

    // Compute the length of each clue
    for (Clue &cl : clues) {
        int solved_cnt = 0;
        if (cl.direction[0] == 'D') {
            int curr_pos = cl.row;
            while (curr_pos < r && grid[curr_pos][cl.col] != '#') {
                if (grid[curr_pos][cl.col] != '.') solved_cnt++;
                curr_pos++;
                cl.clue_size++;
            }
        }
        else {
            int curr_pos = cl.col;
            while (curr_pos < c && grid[cl.row][curr_pos] != '#') {
                if (grid[cl.row][curr_pos] != '.') solved_cnt++;
                curr_pos++;
                cl.clue_size++;
            }
        }
        if (solved_cnt == cl.clue_size) cl.solved = true;
    }
    
    // Solve the given clue by marking the corresponding cells in the grid as non-blank
    function<void(Clue&)> mark = [&](Clue& cl) {
        if (cl.direction[0] == 'D') {
            for (int i = cl.row; i < cl.row + cl.clue_size; i++) {
                if (grid[i][cl.col] == '.') grid[i][cl.col] = 'A';
            }
        }
        else {
            for (int i = cl.col; i < cl.col + cl.clue_size; i++) {
                if (grid[cl.row][i] == '.') grid[cl.row][i] = 'A';
            }
        }
    };

    vector<string> ret;

    while (true) {
        // Update solved status and rank of all clues
        for (Clue &cl : clues) {
            if (cl.solved) continue;
            double cost = double(cl.clue_size * (cl.clue_size + 1) / 2), has_clue = 0.0;
            int val = cl.clue_size, solved_cnt = 0;
            if (cl.direction[0] == 'D') {
                for (int i = cl.row; i < cl.row + cl.clue_size; i++) {
                    if (grid[i][cl.col] != '.') has_clue += val, solved_cnt++;
                    val--;
                }
            }
            else {
                for (int i = cl.col; i < cl.col + cl.clue_size; i++) {
                    if (grid[cl.row][i] != '.') has_clue += val, solved_cnt++;
                    val--;
                }
            }
            if (solved_cnt == cl.clue_size) cl.solved = true;
            else cl.rank = has_clue / cost;
        }

        // Comparator to find the best clue to solve
        auto comp = [&](int a, int b) {
            if (clues[a].rank != clues[b].rank) return clues[a].rank < clues[b].rank;
            if (clues[a].direction[0] != clues[b].direction[0]) return clues[a].direction[0] > clues[b].direction[0];
            return clues[a].clue_no > clues[b].clue_no;
        };

        // Create a heap that will find the next clue to solve
        priority_queue<int, vector<int>, decltype(comp)> pq(comp);

        // Add all unsolved clues into the heap
        for (int i =0; i<len(clues); i++) {
            if (clues[i].solved) continue;
            pq.push(i);
        }

        // If all clues are solved, break the loop
        if (pq.empty()) break;

        // Retrieve and solve the best clue
        int best = pq.top();
        clues[best].solved = true;
        mark(clues[best]);

        // Add the best clue into the answer list
        ret.push_back(to_string(clues[best].clue_no) + clues[best].direction);
    }

    // Print answer list
    for (string s : ret) cout << s << '\n';
}

int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("input.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    H();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}
