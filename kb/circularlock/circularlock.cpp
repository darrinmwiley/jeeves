/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/circularlock
TAGS: math
EXPLANATION: simplify the problem the way the problem statement describes
* 				Using a system of equations with the number of times each button 
* 				is pressed, it is possible if and only if the sum of the numbers on
* 				both diagonals are equivalent mod p
END ANNOTATION
*/

//Suraj Mathashery

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

typedef pair<int, int> pii;

int N;

int gcd(int a, int b){
	if(a == 0) return b;
	if(b == 0) return a;
	return gcd(b, a%b);
}


void process(){
	int s1, s2, s3, s4, p1, p2, p3, p4;
	cin >> s1 >> s2 >> p1 >> p2;
	cin >> s3 >> s4 >> p3 >> p4;
	int p = gcd(gcd(p1, p2), gcd(p3, p4));
	s1 %= p;
	s2 %= p;
	s3 %= p;
	s4 %= p;
	if(((s1 + s4) % p) == ((s2 + s3) % p)) cout << "Yes\n";
	else cout << "No\n";
}

int main(){
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++){
		process();
	}
	return 0;
}
