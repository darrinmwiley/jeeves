/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/alliswell
TAGS: dijkstra
EXPLANATION:
1/ If grid[0][0] is occupied by a person, then return -1
2/ Start from (0, 0), do sparse Dijkstra on the whole graph
3/ For each cell, if it is possible to yell to person A's position, save it for the next Dijkstra, else set it to uninitialized
4/ For each person from 'B' to the last person:
*   4.1/ Start Dijkstra with the distance and position of the cells that are saved in the previous Dijkstra 
*   (e.g: If the current person is B, then Dijkstra will be started with cells that can reach A)
*   4.2/ Repeat step 3 for the current person
* 
* Note: If there is no way to reach any person, return -1
* 
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
 
const int inf = 0x3f3f3f3f;
//const ll inf = 1e15;
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
void printGrid(vector<vector<T>> &grid) {for (int i =0; i<len(grid); i++) {for (int j =0; j<len(grid[i]); j++) { cout << grid[i][j] << '\t';}cout << '\n';}}
template<class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }

#define prayGod main

const int a[]{-1, 1, 0, 0};
const int b[]{0, 0, -1, 1};

int prayGod() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int r,c,p; cin >> r >> c >> p;
    
    vector<pair<int, int>> people_position;
    vector<int> hearing_range(p);
    vector<vector<int>> grid(r, vector<int>(c));

    read(hearing_range, p);
    for (int i = 0; i<r; i++){
        for (int j = 0; j<c; j++) {
            string curr; cin >> curr;
            if (curr[0] >= 65) {
                people_position.emplace_back(i, j);
                grid[i][j] = int(curr[0]);
            }
            else grid[i][j] = stoi(curr);
        }
    }

    if (people_position[0] == make_pair(0, 0)) {
        cout << -1 << '\n';
        return 0;
    }

    sort(people_position.begin(), people_position.end(), [&grid](pair<int, int> a1, pair<int, int> b1) {
        return grid[a1.first][a1.second] < grid[b1.first][b1.second];
    });
    
    for (int i = 0; i<p; i++) grid[people_position[i].first][people_position[i].second] = -1;

    vector<set<pair<int, int>>> graph(p);

    for (int curr = 0; curr<p; curr++) {
        for (int i = 0; i<r; i++) {
            for (int j = 0; j<c; j++) {
                if (grid[i][j] == -1) continue;
                int dist_x = abs(i - people_position[curr].first), dist_y = abs(j - people_position[curr].second);
                if (sqrt(pow(dist_x, 2) + pow(dist_y, 2)) <= hearing_range[curr]) graph[curr].insert(make_pair(i, j));
            }
        }
    }
    
    vector<vector<int>> dist(r, vector<int>(c, inf));
    dist[0][0] = grid[0][0];
    
    auto comp = [&dist](pair<int, int> u, pair<int, int> v) {
        if (dist[u.first][u.second] != dist[v.first][v.second]) return dist[u.first][u.second] < dist[v.first][v.second];
        if (u.first != v.first) return u.first < v.first;
        return u.second < v.second;
    };
    
    set<pair<int, int>, decltype(comp)> q(comp);
    q.insert(make_pair(0, 0));
    
    for (int person = 0; person < p; person++) {
        while (!q.empty()) {
            pair<int, int> curr = *q.begin();
            q.erase(q.begin());
            for (int k = 0; k<4; k++) {
                int new_x = curr.first + a[k], new_y = curr.second + b[k];
                if (!inrange(new_x, 0, r-1) || !inrange(new_y, 0, c-1) || grid[new_x][new_y] == -1) continue;
                if (dist[new_x][new_y] > dist[curr.first][curr.second] + grid[new_x][new_y]) {
                    q.erase({new_x, new_y});
                    dist[new_x][new_y] = dist[curr.first][curr.second] + grid[new_x][new_y];
                    q.insert({new_x, new_y});
                } 
            }
        }
        
        for (int i = 0; i<r && person < p-1; i++) {
            for (int j = 0; j<c && person < p-1; j++) {
                if (!present(graph[person], make_pair(i, j))) dist[i][j] = inf;
                else q.insert(make_pair(i, j));
            } 
        }
    }
    
    int ret = inf;
    for (pair<int, int> pr: graph[p-1]) ret = min(ret, dist[pr.first][pr.second]);
    if (ret != inf) cout << ret << '\n';
    else cout << -1 << '\n';
    
} 

