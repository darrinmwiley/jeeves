/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/race
TAGS: dp, bitmasks, greedy
EXPLANATION:

The dp's aim is to find the minimal time to complete a certain set of tasks.

We represent the set of tasks completed as a bitmask ex.: if tasks 1, 3, and 7 were comleted the mask is 1000101 (lsb).

Because the time it takes to travel between 2 destinations is dependent on direction and the fact that traveling to destinations in a different order can save time, we also have to keep track of the last city visited in the dp state.

Thus, the dp state looks like:
    dp[set of tasks completed][last task completed from the set].

The recurrence is now:
    dp[mask][last_task] = for(all tasks in mask/set not equal to last_task) 
                              min(dp[mask][last_task], dp[mask ^ i][i] + time_to_travel[i][last_task] + time[last_task])
FOR ALL VALID last_tasks's (i.e make sure not to exceed T or deadline[last_task]).

There are special cases for when traveling fromthe start destination to other destinations and also traveling to the final destination.

Finding the lexicographically smallest sequence is easy: just loop for(mask <= 1 << 20) and print out the set represented by the 1st max whose total points is equal to the max total points seen/possible. 

END ANNOTATION
*/


#include <bits/stdc++.h>
#include <limits>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
#define FOR(i, N)         for(int i = 0; i < (N); i++)
#define FORS(i, s, N)     for(int i = (s); i < (N); i++)
#define pb push_back
#define eb emplace_back
using pii = pair<int, int>;
using vi = vector<int> ;
const int MAX_N = 20;
const int MAX_A = 5e5;
const int MAX_Q = 5e5;
const int MAX_SEG = 1 << 20; 
const int INF = numeric_limits<int>::max();

int N, T;

vector<int> masksByBitCount[MAX_N+1];
void genMasksByBitCount() {
  FOR(i, 1<<MAX_N) {
    masksByBitCount[__builtin_popcount(i)].pb(i);
  }
}

// If all the stops rep by mask can''t be reached in time or >T, == INF.
int bestT[1 << MAX_N][MAX_N];
int d[MAX_N];
int t[MAX_N];
int p[MAX_N];
int t_trav[MAX_N+2][MAX_N+2];
int PTot[1 << MAX_N];

void solve() {
  FOR(i, 1<<MAX_N) fill(bestT[i], bestT[i]+MAX_N, INF);
  FOR(i, N) if((t_trav[N][i] + t[i] <= d[i] || d[i] == -1) && t_trav[N][i] + t[i] <= T) bestT[1 << i][i] = t_trav[N][i] + t[i];
 
  FORS(bit_count, 2, N+1) {
    for(int mask : masksByBitCount[bit_count]) {
      if(mask > (1 << N)) continue;

      FOR(last, N){
	if(!((1<<last)&mask)) continue;
	int prev_mask = mask^(1<<last);
	FOR(prev_last, N) {
	  if(prev_last == last || !((1<<prev_last)&prev_mask) || bestT[prev_mask][prev_last] == INF) continue;
	  if((d[last] == -1 || (bestT[prev_mask][prev_last] + t_trav[prev_last][last] + t[last]) <= d[last]) && (bestT[prev_mask][prev_last] + t_trav[prev_last][last] + t[last] <= T))
	    bestT[mask][last] = min(bestT[mask][last], bestT[prev_mask][prev_last] + t_trav[prev_last][last] + t[last]);
	}
      }
    }
  }

  int maxP = 0;
  FOR(i, 1<<N) {
    int minT = INF;
    bool maskPossible = 0;
    for(int j = 0; j < N && !maskPossible; j++) { 
      if(bestT[i][j] <= T && bestT[i][j] + t_trav[j][N+1] <= T) 
	maskPossible = true; 
    }
    int pTot = 0;
    if(maskPossible) 
      FOR(j, N) if((1<<j)&i) pTot += p[j];

    PTot[i] = pTot;
    maxP = max(pTot, maxP);
  }

  if(maxP == 0){
    cout << 0 << endl; return;
  }
  
  FOR(i, 1 << N) {
    if(PTot[i] == maxP) {
      cout << maxP << endl;
      FOR(j, N) if ((1<<j)&i) cout << j+1 << " ";
      return;
    }
  }
  
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

  cin >> N >> T;
  FOR(i, N) cin >> p[i] >> t[i] >> d[i];
  FOR(i, N+2) FOR(j, N+2) cin >> t_trav[i][j];

  genMasksByBitCount();
  solve();
  
  return 0;
}
