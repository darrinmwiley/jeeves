/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/speedlimit2
TAGS: Tree, DFS, DP
EXPLANATION:

The main goal for this problem is for all weights to each vertex be equal
if they do not have a speed limit sign.

DP Cases:
1. If we make all the weights equal we must check all children for the weights to be equal.
    - DP_w = SUM {DP_w...}
2. If we put in a sign, the edges don't have to be of equal weights.
    - c*deg_v + SUM{best...}
        where best is the minimum of all dp values of this vertex.
    For this case we also need to consider changing the weight of the outgoing edge, as
    it may be beneficial to the next vertex.
END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define INF numeric_limits<int>::max();

void solve() {
    int n, c;
    cin >> n >> c;
    vector<vector<pair<int, int>>> adj(n);
    vector<int> speeds;

    for(int i = 0; i < n-1; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        --a; --b;
        adj[a].emplace_back(b, s);
        adj[b].emplace_back(a, s);
        speeds.push_back(s);
    }
    sort(all(speeds));
    // erase unique values for memory optimization
    speeds.erase(unique(all(speeds)), speeds.end());
    reverse(all(speeds));

    vector<vector<int>> vt(n);

    auto dfs = [&](auto self, int root, int skip) {
        int bnt = c*adj[root].size();
        int mx = 0, up = 0;
        for(auto i : adj[root]) {
            mx = max(mx, i.second);
            if(i.first == skip) up = i.second;
        }

        int count = speeds.size();
        while(count>0&&speeds[count-1]<mx)--count;
        vt[root].resize(count);
        auto& best = vt[root];
        for(int i = 0; i < count; i++) {
            if(up > 0) {
                best[i] = speeds[i] - up;
            }
        }

        if(root == -1) {
            return bnt;
        }

        for(auto a : adj[root]) {
            if(a.first == skip) continue;
            auto cnt = self(self, a.first, root);
            const auto& ct = vt[a.first];
            int bc = cnt;
            for(auto x : ct) bc = min(bc, x);
            bnt+=bc;
            for(int i = 0; i < count; i++) {
                int cur = cnt + speeds[i] - a.second;
                if(i < ct.size()) cur = min(cur, ct[i]);
                best[i] += cur;
                
            }
        }
        return bnt;
    };

    int best = dfs(dfs, 0, -1);
    for(int x : vt[0]) best = min(best, x);
    cout << best << endl;
}

int main() {
    solve();
}