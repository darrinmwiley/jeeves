/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/barcode
TAGS: combinations, modulus
EXPLANATION:
The number of barcodes without consecutive blue bars with size n can be found by adding the twice the number of nonconsecutive barcodes ending with red of size n-1 and barcodes ending with blue of size n-1
 This sequence fits the fibonacci sequence, where there is 2 possible barcodes at n=1 and 3 possible barcodes at n=2
 The number of barcodes with equal number of red and blue bars can only be found for barcodes of even size and is n choose n/2
 This is since there is n*n-1*n-2...n/2+1 spots to place blue barcodes and n/2*n/2-1*n/2-2...1 equivalent placements (There are n/2*n/2-1...1 spots for red barcodes but also n/2*n/2-1...1 equivalent placements)
 The calculation of n choose n/2 can be simplified in which evens in the numerator simplify into 2, the prime m can be divided out, and the mod inverse of the remaining denominator can be found ^m-2 since m is prime
 If the numerator contains more factors of m than the denominator, the solution is zero
 If the size is even, there are n/2+1 overlaps since the extra red bar can be placed in n/2+1 positions when both rules are true
END ANNOTATION
*/

#include <iostream>
#include <cmath>
using namespace std;
#define N 1000001

int fib(int n, int m){
    int a = 1%m, b = 2%m;
    for(int i = 2; i<=n; i++){
        int x = (a+b)%m;
        a=b;
        b=x;
    }
    return b;
}

int ncn(int n, int m){
    long long r = 1, q = 1, a = 0, b = 0, c;
    //numerator
    for(int i = n; i>n/2; i--){
        if(i%2) c=i;
        else c=2;
        while(!(c%m)){
            c/=m;
            a++;
        }
        r=(r*c)%m;
    }
    //denominator
    for(int i = n/4; i>0; i--){
        c=i;
        while(!(c%m)){
            c/=m;
            b++;
        }
        q = (q*(c%m))%m;
    }
    if(a>b) return 0;
    //mod inv
    long long x = 1, y = m-2;
    while(y){
        if(y&1) x = (x*q)%m;
        y = y>>1;
        q = (q*q)%m;
    }
    return (r*x)%m;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int d, n, m, k;
    cin>>d;
    for(int i = 0; i<d; i++){
        cin>>n>>m;
        k = fib(n,m);
        if(!(n%2)) k+=(ncn(n,m)-n/2-1)%m;
        while(k<0) k+=m;
        cout<<k%m<<endl;
    }
}
