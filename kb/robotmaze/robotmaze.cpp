/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/robotmaze
TAGS: bfs
EXPLANATION:
- Do a 3-state bfs from robot's starting position
   + State 1: current position
   + State 2: the direction from which the robot enters the current position
   + State 3: whether the robot's 2 most recent moves upon reaching the current position are the same
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

/*
a[i] and b[i] will help determines the next cell that the robot will enter by traversing in the i-th direction
(0: up, 1 : down, 2: left, 3: right)
dir[i] will determine the direction from which the robot will enter the next cell
(e.g: If the robot goes from cell A to cell B by going up, it will enter cell B from cell B's bottom border)
*/
const int a[]{-1, 1, 0, 0};
const int b[]{0, 0, -1, 1};
const int dir[]{1, 0, 3, 2};
 
void prayGod() {
    int t; cin >> t;
    while (t--) {
        // I/O
        int n,m; cin >> n >> m;
        char grid[n][m];
        pair<int, int> start, dest;
        for (int i = 0; i<n; i++) {
            string s; cin >> s;
            for (int j = 0; j<m; j++) {
                grid[i][j] = s[j];
                if (s[j] == 'R') start = make_pair(i, j);
                else if (s[j] == 'D') dest = make_pair(i, j);
            }
        }

        deque<pair<pair<int, int>, pair<int, int>>> q;
        int dist[n][m][4][2];

        // Initialize distance value as infinity for all state except those that are at the starting position (which will be set to 0)
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                for (int k = 0; k<4; k++) {
                    for (int z = 0; z<2; z++) {
                        if (i != start.first || j != start.second) dist[i][j][k][z] = iinf;
                        else dist[i][j][k][z] = 0;
                    } 
                }
            }
        }
        
        // Initialize distance for starting cell's neighbors
        for (int k = 0; k<4; k++) {
            int new_x = start.first + a[k], new_y = start.second + b[k];
            if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] == 'B') continue;
            dist[new_x][new_y][dir[k]][0] = 1;
            q.emplace_back(make_pair(new_x, new_y), make_pair(dir[k], 0));
        }

        // BFS
        while (!q.empty()) {
            pair<pair<int, int>, pair<int, int>> curr = q.front();
            q.pop_front();

            // If the robot's 2 most recent moves upon reaching current position are not the same
            if (!curr.second.second) {
                for (int k = 0; k<4; k++) {
                    // Make sure that the robot will not go back to where it came from
                    if (k == curr.second.first) continue;

                    // Check if it is possible to reach the new cell
                    int new_x = curr.first.first + a[k], new_y = curr.first.second + b[k];
                    if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] == 'B') continue;

                    // Check if the direction of the next step is the same as the direction from which the robot enters the current cell
                    int step = (k/2 == curr.second.first/2);    

                    // Distance that the robot travels so far (upon reaching the current position)
                    int currDist = dist[curr.first.first][curr.first.second][curr.second.first][curr.second.second];

                    // Update the min distance if necessary
                    if (dist[new_x][new_y][dir[k]][step] > currDist + 1) {
                        dist[new_x][new_y][dir[k]][step] = currDist + 1;
                        q.emplace_back(make_pair(new_x, new_y), make_pair(dir[k], step));
                    }
                }
            }
            // Else
            else {
                // Only check direction that is different from the previous direction
                int bound = (!(curr.second.first/2))*2;
                for (int k = bound; k < bound + 2; k++) {
                    // Check if it is possible to travel to the new cell
                    int new_x = curr.first.first + a[k], new_y = curr.first.second + b[k];
                    if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] == 'B') continue;
                    
                    // Distance that the robot travels so far (upon reaching the current position)
                    int currDist = dist[curr.first.first][curr.first.second][curr.second.first][curr.second.second];
                    
                    // Update the min distance if necessary
                    if (dist[new_x][new_y][dir[k]][0] > currDist + 1) {
                        dist[new_x][new_y][dir[k]][0] = currDist + 1;
                        q.emplace_back(make_pair(new_x, new_y), make_pair(dir[k], 0));
                    }
                }
            }
        }

        // Find min distance for destination cell
        int ret = iinf;
        for (int k =0 ; k<4; k++) {
            for (int z = 0; z < 2; z++) ret = min(ret, dist[dest.first][dest.second][k][z]);
        }

        cout << (ret != iinf ? ret : -1) << '\n';

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
