/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/stoichiometry
TAGS: Matrices, Factorization
EXPLANATION:
The combination of molecules so that both sides are equal is the same as finding the null space of a matrix in which the elements are rows and molecules are columns and right hand molecules are negative
Turning the input into a matrix can be done by taking string inputs and assigning each element a row with a map
Reducing the matrix can be done for each row by multiplying a row to the lcm of the pivot row and subtracting each for each element times lcm/pivot
The nullspace vector can be found by moving up the matrix and finding the next value starting with m=1 (finding a multiple can similarly be done by gcd/current element and multipying the rest by gcd/sum of found*row)
END ANNOTATION
*/
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

int c[21][21], C[21], n, m;
map<string, int> e;

void print(){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
}

void fill(istream& in){
    m = 0; n = 0;
    string x;
    while(true){
        getline(in, x);
        int s;
        if(x.at(0)=='+') s=1;
        else if(x.at(0)=='-') s=-1;
        else return;
        int N = x.at(3)-48;
        int p = 5;
        for(int i = 0; i<N; i++){
            string y = x.substr(p,x.find(' ',p)-p);
            p+=y.size()+1;
            int z = stoi(x.substr(p,x.find(' ',p)-p));
            p+=x.substr(p,x.find(' ',p)-p).size()+1;
            map<string, int>::iterator it = e.find(y);
            if(it!=e.end()) c[e[y]][m]+=s*z;
            else{
                e[y] = n;
                c[n][m]+= s*z;
                n++;
            }
        }
        m++;
    }

}
void solve(){
    for(int i = 0; i<m-1; i++){
        if(!(c[i][i])){
            for(int j = i+1; j<n; j++){
                if(c[j][i]){
                    for(int k = 0; k<m; k++) swap(c[i][k],c[j][k]);
                    break;
                }
            }
        }
        for(int j = i+1; j<n; j++){
            int l = lcm(c[j][i],c[i][i]);
            if(!(l)) continue;
            for(int k = i+1; k<m; k++){
                c[j][k] *= l/c[j][i];
                c[j][k] -= c[i][k]*(l/c[i][i]);
            }
            c[j][i] = 0;
        }
    }
    C[m-1] = 1;
    for(int i = m-2; i>=0; i--){
        int r = 0;
        for(int j = n; j>i; j--) r+=C[j]*c[i][j];
        int g = gcd(r,c[i][i]);
        C[i] = -1*r/g;
        for(int j = m; j>i; j--) C[j]*=c[i][i]/g;
    }

    bool q = true;
    for(int i = 0; i<m; i++){
        if(C[i]>0){q=false; break;}
    }
    if(q) for(int i = 0; i<m; i++) C[i]*=-1;
}



int main(){
    fill(cin);
    solve();
    for(int i = 0; i<m; i++) {cout<<C[i]; if(i<m-1) cout<<" ";}
}
