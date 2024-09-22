/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/quests
TAGS: sorting, knapsack, dp, bitset
EXPLANATION:
Idea: We want to select the maximum weight set of quests such that they can all
be scheduled while underleveled.

let the "slack" of a quest be the amount of xp you're allowed to receive while
remaining underleveled.

Observation 1: a set can be scheduled if and only if it can be scheduled in
order of ascending (C*reward + slack).

This observation comes from mapping to this problem:
https://open.kattis.com/problems/installingapps

You can think of s_i as reward and d_i as (total XP-slack). This is equivalent
to disallowing selection if you're not underleveled.

solutions for the contest installingapps came from are here:
https://people.bath.ac.uk/masjhd/NWERC/news/index.html#Solutions

and in their solution they list this observation.

We can solve this with a dp of the form dp[Q][X] = 1 if you can gain XP points
while underleveled within the first Q quests.

dp[Q][X+reward] = 1 if dp[Q][X] = 1 and X is underleveled for quest Q

By using the sorting scheme above we guarantee that any valid sort is achieveable
with our DP

the only problem left is the size of the DP.

Optimization 1: notice that you're only getting rewards in multiples of C since
you want all quests to be underleveled. So store XP/C instead of XP and do math
to figure out what is overleveled

Optimization 2: use bitset to do knapsack-like DP 32 times faster -
https://codeforces.com/blog/entry/73558

Last, use math to figure out the sum of quest XP from the quests you did not
schedule while underleveled, and report the result.
END ANNOTATION
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct quest{

    long overlevelThreshold;
    int maximumXP;
    int reward;
    int CReward;

    const bool operator< (const quest &q) const{
        return overlevelThreshold + CReward < q.overlevelThreshold+q.CReward;
    }

}quests[2000];

int main() {
    int N,V,C;
    cin >> N >> V >> C;
    int baseSum = 0;
    for(int i = 0;i<N;i++)
    {
        int x, d;
        cin >> x;
        cin >> d;
        baseSum += x;
        quests[i].reward = x;
        quests[i].CReward = x*C;
        quests[i].overlevelThreshold = (long)(d)*V;
        quests[i].maximumXP = (long)(d)*V/C;
        if((long)(d)*V % C == 0)
            quests[i].maximumXP--;
    }
    sort(quests, quests+N);
    bitset<4000001> dp[N+1];
    dp[0][0] = 1;
    for(int i = 0;i<N;i++)
    {
        bitset<4000001> mask;
        mask.flip();
        mask = mask >> (quests[i].maximumXP+1) << (quests[i].maximumXP+1);
        mask.flip();
        dp[i+1] |= (dp[i] & mask) << quests[i].reward;
        dp[i+1] |= dp[i];
    }
    long xp = 0;
    for(int i = 0;i<4000001;i++)
    {
        if(dp[N][i])
            xp = i;
    }
    long ans = baseSum - xp + xp*C;
    cout << ans;
}
