/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/fire3
TAGS: bfs, queue
EXPLANATION:
Have a grid (fireVisited) where fireVisited[row][col] is the min time for any fire to reach (row, col)
Do this by initially setting it to a large number then doing multiple BFSes for each fire.
Then do a BFS for John. If he takes more time to reach a square than the fire does (fireVisited), don't add that square to the queue. Otherwise, add it to the queue and set the min # of steps required to reach that square (locs[r][c]).
  In the BFS when you reach a square on the border of the grid, min your answer with the steps required to reach that border.
If you never reached a border in John's BFS, it is IMPOSSIBLE.
Otherwise print the min # of steps.
END ANNOTATION
*/
#include <iostream>
using namespace std;

#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define endl "\n"
#define fi first
#define se second

#include <string>
#include <vector>
typedef vector<int> vi;
#include <cstring>
#include <queue>

int rows, cols;
vector<vector<char> > grid;
vector<vector<int> > fireVisited;
//Returns whether the row, col is inside the grid
bool canDo(int x, int y) {
    return ((x >= 0 && x <= rows - 1) && (y >= 0 && y < cols));
}
int xs[] = {0, 0, 1, -1};
int ys[] = {-1, 1, 0, 0};
void bfs(int r, int c) {
    queue<pair<int, int> > q;
    q.push(mp(r, c));
    fireVisited[r][c] = 0;
    vector<vector<bool> > visited;
    visited.resize(rows, vector<bool>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) visited[i][j] = 0;
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        if (visited[p.first][p.second]) continue;
        visited[p.first][p.second] = 1;
        for (int i = 0; i < 4; i++) {
            int x = xs[i] + p.first;
            int y = ys[i] + p.se;
            if (!canDo(x, y) || grid[x][y] == '#') continue;
            if (fireVisited[x][y] > fireVisited[p.fi][p.se] + 1) {
                fireVisited[x][y] = fireVisited[p.fi][p.se] + 1;
                q.push(mp(x, y));
            }
        }
    }
}
// True if John is on the border of the grid and can escape
bool isBorder(int x, int y) {
    return (x == 0 || x == rows - 1 || y == 0 || y == cols - 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> rows >> cols;
    grid.resize(rows, vector<char>(cols));
    fireVisited.resize(rows, vector<int>(cols));

    int jx, jy;
    vector<pii> fires;
    for (int i = 0; i < rows; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < cols; j++) {
            grid[i][j] = s[j];
            if (s[j] == 'J')
                jx = i, jy = j;
            else if (s[j] == 'F') {
                fireVisited[i][j] = 1;
                fires.pb(mp(i, j));
            }
            if (s[j] != 'F') {
                fireVisited[i][j] = 100000;
            }
        }
    }

    for (pair<int, int> f : fires) {
        bfs(f.first, f.se);
    }

    int locs[rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            locs[i][j] = 1000000;

    queue<pair<int, int> > q;
    q.push(mp(jx, jy));
    bool visited[rows][cols];
    memset(visited, false, sizeof(visited));
    int steps = 100000;
    locs[jx][jy] = 0;
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        if (visited[p.first][p.second]) continue;
        visited[p.first][p.second] = 1;
        if (isBorder(p.fi, p.se))
            steps = min(steps, locs[p.fi][p.se]);
        
        
        for (int i = 0; i < 4; i++) {
            int x = xs[i] + p.first;
            int y = ys[i] + p.se;
            if (!canDo(x, y) || grid[x][y] != '.') continue;
            if (locs[x][y] > locs[p.fi][p.se] + 1) {
                locs[x][y] = locs[p.fi][p.se] + 1;
                if (locs[x][y] >= fireVisited[x][y])
                    continue;
                else
                    q.push(mp(x, y));
            }
        }
    }
    if (steps == 100000)
        cout << "IMPOSSIBLE";
    else
        cout << steps + 1;
}
