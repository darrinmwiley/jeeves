/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/gcdharmony
TAGS: graph, dp
EXPLANATION: Choose a root node with degree one and visit nodes of the tree from the bottom up. Using dp to store results,
find the cost of maintaining gcd harmony in a subtree and changing its root node to a value v for all v between [1,10000]
and composed of primes between [1,100] by adding the cost of its children and changing the chosen node's value. The costs
found for a subtree of for value v can be used in a minimum between other values that also contain a common prime factor of v
in calculating the parent's cost.
END ANNOTATION
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int vals[5001];
vector<int> adj[5001];
bool vis[5001];
int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int f[5001][4001];

int main(){
    int n;
    cin>>n;    
    for(int i = 1; i<=n; i++){
        int a;
        cin>>a;
        vals[i]=a;
    }
    for(int i = 0; i<n-1; i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int r = -1;
    for(int i = 0; i<n; i++){
        if(adj[i].size()==1){
            r = i;
        }
    }
    vector<int> ord;
    int slider = 0;
    ord.push_back(r);
    vis[r]=true;
    while(ord.size()<n){
        for(int i = 0; i<adj[ord[slider]].size(); i++){
            if(vis[adj[ord[slider]][i]]) continue;
            else{
                ord.push_back(adj[ord[slider]][i]);
                vis[adj[ord[slider]][i]] = true;
            }
        }
        slider++;
    }

    //finds 3715 numbers
    vector<int> nvals;
    vector< vector<int> > factors;
    for(int i = 1; i<10001; i++){
        int x = i;
        vector<int> fs;
        for(int j = 0; j<25; j++){
            bool y = true;
            while(x%primes[j]==0){
                x/=primes[j];
                if(y) fs.push_back(j);
                y=false;
            }
        }
        if(fs.size()>0&&x==1){
            nvals.push_back(i);
            factors.push_back(fs);
        }
    }

    for(int i = 0; i<=n; i++) vis[i]=false;
    for(int i = n-1; i>0; i--){
        int c, p = ord[i], h[25];
        for(int j = 0; j<25; j++) h[j] = 20001;
        vis[p] = true;
        for(int o = 0; o<nvals.size(); o++){
            int v = nvals[o];
            c = 0;
            for(int j = 0; j<adj[p].size(); j++){
                if(vis[adj[p][j]]){
                    c += 20001-f[adj[p][j]][o];
                }
            }
            if(vals[p]!=v) c+=v;
            for(int j = 0; j<factors[o].size(); j++){
                    h[factors[o][j]] = min(h[factors[o][j]],c);
            }
        }
        for(int o = 0; o<nvals.size(); o++){
            int v = nvals[o];
            for(int k = 0; k<factors[o].size(); k++){
                if(h[factors[o][k]]<20001-f[p][o]){
                    f[p][o] = 20001-h[factors[o][k]];
                }
            }
        }
    }
    int m = 200001;
    for(int o = 0; o<nvals.size(); o++){
        int v = nvals[o];
        int c = 0;
        for(int i = 0; i<adj[r].size(); i++){
            c+=20001-f[adj[r][i]][o];
        }
        if(v!=vals[r]) c+=v;
        m = min(m,c);
    }
    cout<<m<<endl;
}