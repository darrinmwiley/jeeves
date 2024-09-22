/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/produktsiffra
TAGS: brute-force, combinatorics
EXPLANATION: All that matters is the number of each digit, not their order
* 				We can brute force every way to distrubute 15 digits among
* 				10 possible options. We also need to account for every
* 				possible way to make a number in the valid range with
* 				the digits.
* 
END ANNOTATION
*/

//Suraj Mathashery

#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <cassert>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int MAXLOG = 15;

ll L, R;
ll ans[9];
ll p10[16];
ll comb[20][20];

long long combin(vector<int> &v){
    int s = 0;
    for(int c : v){
        s += c;
    }
    ll res = 1;
    for(int c : v){
        res *= comb[s][c];
        s -= c;
    }
    return res;
}

long long numBelow(long long V, vector<int> v){
    ll ans = 0;
    for(int i = MAXLOG-1; i >= 0; i--){
        int mx = V / p10[i];
        for(int e = 0; e < mx; e++){
            if(v[e] > 0){
                v[e]--;
                ans += combin(v);
                v[e]++;
            }
        }
        if(v[mx] > 0)
            v[mx]--;
        else
            break;
        V %= p10[i];
        if(i == 0) ans++;
    }
    return ans;
}

void process(vector<int> &v){
    if(v[0] == MAXLOG) return;
    long long tmp = 1;
    for(int i = 1; i <= 9; i++){
        for(int e = 0; e < v[i]; e++){
            tmp *= i;
        }
    }
    while(tmp >= 10) {
        ll res = 1;
        while(tmp > 0){
            if(tmp%10 != 0) res *= (tmp%10);
            tmp /= 10;
        }
        tmp = res;
    }
    
    ans[tmp-1] += numBelow(R, v) - numBelow(L-1, v);
}

void dfs(int s, vector<int> &v){
    if(v.size() == 10){
        if(s == 0){
            process(v);
        }
        return;
    }
    for(int i = 0; i <= s; i++){
        v.push_back(i);
        dfs(s-i, v);
        v.pop_back();
    }
}

int main(){
    cin >> L >> R;
    p10[0] = 1;
    for(int i = 1; i < 16; i++){
        p10[i] = 10*p10[i-1];
    }
    if(R == p10[15]){
        ans[0]++;
        R--;
    }
    
    comb[0][0] = 1;
    for(int i = 1; i < 20; i++){
        comb[i][0] = comb[i][i] = 1;
        for(int e = 1; e < i; e++){
            comb[i][e] = comb[i-1][e-1] + comb[i-1][e];
        }
    }
    
    vector<int> v;
    dfs(MAXLOG, v);
    
    for(int i = 0; i < 9; i++) cout << ans[i] << " ";
    cout << endl;
    
    return 0;
}
