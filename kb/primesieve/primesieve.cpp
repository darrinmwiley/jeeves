/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/primesieve
TAGS: Sieve
EXPLANATION: Sieve of Eratosthenes
END ANNOTATION
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long n;
    int q;
    long x;
    long numPrimes = 0;
    cin >> n;
    cin >> q;
    vector<bool> nums(n + 1 , true);
    nums[0] = false;
    nums[1] = false;
    long sqrtN = sqrt(n);
    for(long i = 2; i < n+1; i++){
        if(!nums.at(i)){continue;}
        else {
            numPrimes++;
            for(long j = i*i; j < n+1; j+=i){
                nums.at(j) = false;
            }
        }
    }
    cout << numPrimes << "\n";
    for (int i = 0; i < q; i++) {
        cin >> x;
        cout << nums.at(x) << "\n";
    }
    return 0;
}
