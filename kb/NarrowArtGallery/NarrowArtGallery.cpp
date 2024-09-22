/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/narrowartgallery
TAGS: dp
EXPLANATION:
3D dp table. dp[row][col][k] is min cost to have k rooms closed from room (row,col) to the bottom of the hall. Note: dp[row][col][k] does not necessarily have to have room (row, col) closed.
See comments for dp states
END ANNOTATION
*/

#include <iostream>
using namespace std;

#define ll long long
#define rs resize
#define min_self(a, b) a = min(a, b);

#include <vector>
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

void not_needed() {
    int a;
    cin >> a >> a;
}

#define INF 100000000
int n, k;
vvi grid;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    grid.resize(n, vi(2));
    for (int tr = 0; tr < n; tr++) {
        cin >> grid[tr][0] >> grid[tr][1];
    }
    not_needed();

    int dp[n + 3][2][k];
    for (int i = 0; i < n + 3; i++)
        for (int j = 0; j < k; j++) dp[i][0][j] = dp[i][1][j] = INF;

    for (int row = n - 1; row >= 0; row--) {
        for (int col = 0; col < 2; col++) {
            // The minimum of row, col with only one number
            // is min of value there (in grid) or min for the 1 below it dp[row+1][col][0]
            // or the one that is a knight's move away dp[row +2][1-col][0]
            dp[row][col][0] = min(dp[row + 1][col][0], min(dp[row + 2][1 - col][0], grid[row][col]));
            int value = grid[row][col];
            for (int j = 1; j < k; j++) {
                // min of row, col with j numbers is min of row below with j #s or row below with j - 1 #s + current row, col as jth number
                dp[row][col][j] = min(dp[row + 1][col][j - 1] + value, dp[row + 1][col][j]);
                // Same as before but with box on the other side
                dp[row][col][j] = min(dp[row][col][j],
                                      min(dp[row + 2][1 - col][j - 1] + value, dp[row + 2][1 - col][j]));
            }
        }
    }
    int answer = INF;
    ll sum = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < 2; col++) {
            min_self(answer, dp[row][col][k - 1]);
            sum += grid[row][col];
        }
    }
    cout << sum - answer << endl;
}
