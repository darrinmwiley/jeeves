/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/maxflow
TAGS: max flow
EXPLANATION:
this is straightforward maxflow.
This solution can serve as a reference for a clean c++ implementation of Edmunds-Karp using edge structs.
Motivation behind struct for edges is memory efficiency in sparse graphs.
END ANNOTATION
*/
#include "bits/stdc++.h"

using namespace std;

#define pb push_back
#define boolean bool
#define li long long int

int N, M, S, T;

li INF = LONG_MAX/4;

struct edge{
    int to;
    li cap;
    //if we block together edges/reverses in groups of 2, we can get reverse by xor with 1
};

vector<int> adj[500];
vector<edge> e;

li aug(int s, int t)
{
    vector<bool> vis(500, 0);
    vis[s] = 1;
    vector<int> p(500, -1);
    queue<pair<int, li> > que;//(location, flow)
    que.push(make_pair(s, INF));
    while(!que.empty())
    {
        auto curr = que.front();
        int loc = curr.first;
        li flow = curr.second;
        que.pop();

        if(loc == t)
        {
            int curr = t;
            while(p[curr] != -1)
            {
                e[p[curr]].cap -= flow;
                e[p[curr]^1].cap += flow;
                curr = e[p[curr]^1].to;
            }
            return flow;
        }

        for(int x: adj[loc])
        {
            edge ed = e[x];
            int next = ed.to;
            if(!vis[next] && ed.cap > 0)
            {
                que.push(make_pair(next, min(flow, ed.cap)));
                vis[next] = true;
                p[next] = x;
            }
        }
    }
    return 0;
}

li maxflow(int S, int T)
{
    li flow = 0;
    while(true){
        li increase = aug(S, T);
        if(increase != 0)
            flow += increase;
        else{
            return flow;
        }
    }
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> S >> T;
	for(int i = 0;i<M;i++)
    {
        int u, v;
        li x;
        cin >> u >> v >> x;
        struct edge e1 = {v,x};
        struct edge e2 = {u,0};
        e.pb(e1);
        e.pb(e2);
        adj[u].pb(i*2);
        adj[v].pb(i*2+1);
    }
    li flow = maxflow(S,T);
    int used = 0;
    for(int j = 0;j<M;j++)
    {
        if(e[j*2+1].cap != 0)
            used++;
    }
    cout << N << " "<<flow<<" "<<used<<endl;
    for(int j = 0;j<M;j++)
    {
        int amt = e[j*2+1].cap;
        int from = e[j*2+1].to;
        int to = e[j*2].to;
        if(amt != 0)
            cout << from << " "<<to<<" "<<amt<<endl;
    }
}
