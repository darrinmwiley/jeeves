/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/herrings
TAGS: Dynamic programming
EXPLANATION: 
Let's think about a simplified version of this problem.
Let's assume L is 0, meaning every pool can have any
    number of herrings.
If we know the number of ways to divide each of, say, 
    N%10, 10 + N%10, and 20 + N%10 herrings into 3 pools, 
    we can proceed by finding the number of combinations 
    for N/10, N/10 - 1, N/10 - 2 and then multiplying the 
    results. Solving the problem of 20 + N%10 herrings is 
    finding out the number of ways to get the least 
    significant digit + a 20 carry term.  N/10 - 2 removes 
    the 20 carry term.
So, this inspires the solution of dp, where dp_i,j is 
    the number of combinations to get N%(10^i) + j*10^i.
    i represents the index on N and j represents the carry
    term.
This means dp_i,j = C(N[i]+10j-0)*dp_(i-1),0 + C(N[i]+10j-1)
    *dp_(i-1),1 + C(N[i]+20j-2)*dp_(i-1),2 where C(x) is the
    number of ways to add 3 one-digit non-3 numbers to get x.
Then, I want to find dp_(|N-1|),0

To include L, must include another dimension to the dp : k. 
    k is like a bitmask saying which pools have already
    surpassed the lower limit for sure. 
If each (i,j,k) takes a constant amount of time to compute,
    then the time is O(|N|) since there are only 3 possible
    carry terms and 2 possible comparison results for each 
    N index.
I use dp_0,j,k as a base case.
END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll dp[10000][3][1 << 3];
int Nlen,Llen;
int N[10000],L[10000];
ll mod=12345647ll;

ll f(int i,int j,int k) {
    if (dp[i][j][k]!=-1) return dp[i][j][k];
    int fg,sg,tg; // processing on k
    fg=k%2,sg=(k/2)%2,tg=(k/4)%2;
    int target = (N[i])+10*j;
    ll sum=0;
    if (i==0) {
        for (int subJ=0;subJ<1;subJ++) {
            int newTarget = target-subJ;
            for (int l=0;l<100;l++) {
                int n1=l%10,n2=(l/10)%10;
                int n3=newTarget-n1-n2;
                if ((n1==3 || n2==3) || n3==3) continue;
                if (n3 < 0 || n3 > 9) continue;
                if (n1 < L[i] && fg==0) continue;
                if (n2 < L[i] && sg==0) continue;
                if (n3 < L[i] && tg==0) continue;
                sum = (sum + 1ll)%mod;
            }
        }
        dp[i][j][k] = sum;
        return sum;
    }
    for (int subJ=0;subJ<3;subJ++) {
        int newTarget = target-subJ;
        for (int l=0;l<100;l++) {
            int n1=l%10,n2=(l/10)%10;
            int n3=newTarget-n1-n2;
            if ((n1==3 || n2==3) || n3==3) continue;
            if (n3 < 0 || n3 > 9) continue;
            int newK=k;
            if (i < Llen) {
                if (n1 < L[i] && fg==0) continue;
                if (n2 < L[i] && sg==0) continue;
                if (n3 < L[i] && tg==0) continue;
                if (n1>L[i] && fg==0) newK += 1;
                if (n2>L[i] && sg==0) newK += 2;
                if (n3>L[i] && tg==0) newK += 4;
            }
            else {
                if (n1 > 0 && fg==0) newK += 1;
                if (n2 > 0 && sg==0) newK += 2;
                if (n3 > 0 && tg==0) newK += 4;
            }
            sum = (sum + f(i-1,subJ,newK))%mod;
        }
    }
    dp[i][j][k] = sum;
    return sum;
}

int main() {
    int T;
    cin >> T;
    while (T --> 0) {
        string Nstr,Lstr;
        cin >> Nstr >> Lstr;
        for (int i=Nstr.size()-1;i>=0;i--) 
            N[Nstr.size()-1-i] = Nstr[i]-'0';
        for (int i=Lstr.size()-1;i>=0;i--) 
            L[Lstr.size()-1-i] = Lstr[i]-'0';
        Nlen = Nstr.size();
        Llen = Lstr.size();
        for (int i=0;i<Nlen;i++) {
            for (int j=0;j<3;j++) {
                for (int k=0;k<8;k++) dp[i][j][k] = -1;
            }
        }
        cout << f(Nlen-1,0,0) << endl;
    }
}