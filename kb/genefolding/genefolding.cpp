/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/genefolding
TAGS: math
EXPLANATION: We make a rolling hash of the string, and do the same in the reverse direction
* Observation 1: We can iterate from the left, folding the first chance we can
* 					We see this by noticing that if we can make a bigger fold,
* 					the same result will be achieved anyways by greedily doing
* 					smaller folds
* 
* We do this from both the left and the right side.
* 
* Note: One bug was that I forgot to restart at the beginning of the string
* whenever I folded it.
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

typedef long long ll;

const int numMod = 3;

string s;
vector<int> hsh[numMod], rhsh[numMod];
vector<int> pw[numMod];
int mods[numMod] = {1000000009, 1000000007, 1000000021};
int alpha = 5;

int mult(int a, int b, int m){
	return (int) ((long long) a * b % m);
}

int mod(int a, int m){
	if(a >= m) a -= m;
	return a;
}

int ad(int a, int b, int m){
	a += b;
	return mod(a, m);
}

int sub(int a, int b, int m){
	a = a - b + m;
	return mod(a, m);
}

int trans(char c){
	if(c == 'A') return 1;
	if(c == 'G') return 2;
	if(c == 'T') return 3;
	if(c == 'C') return 4;
	return 4;
}

int getHash(int b, int e, int m){
	return sub(hsh[m][e+1], mult(hsh[m][b], pw[m][e-b+1], mods[m]), mods[m]);
}

int getRhash(int b, int e, int m){
	return sub(rhsh[m][b], mult(rhsh[m][e+1], pw[m][e-b+1], mods[m]), mods[m]);
}

bool symmetric(int b, int e){
	for(int m = 0; m < numMod; m++){
		int mid = (e + b) / 2;
		int h = getHash(b, mid, m);
		int rh = getRhash(mid+1, e, m);
		if(h != rh) return false;
	}
	return true;
}

int main(){
    cin >> s;
    
    for(int i = 0; i < numMod; i++){
		hsh[i] = vector<int>(s.size()+1);
		rhsh[i] = vector<int>(s.size()+1);
		pw[i] = vector<int>(s.size() + 1);
		pw[i][0] = 1;
		for(int e = 1; e <= s.size(); e++){
			pw[i][e] = mult(pw[i][e-1], alpha, mods[i]);
		}
		hsh[i][0] = 0;
		rhsh[i][s.size()] = 0;
	}
    
    for(int i = 0; i < s.size(); i++){
		for(int m = 0; m < numMod; m++){
			hsh[m][i+1] = ad(mult(hsh[m][i], alpha, mods[m]), trans(s[i]), mods[m]);
		}
	}
	for(int i = s.size() - 1; i >= 0; i--){
		for(int m = 0; m < numMod; m++){
			rhsh[m][i] = ad(mult(rhsh[m][i + 1], alpha, mods[m]), trans(s[i]), mods[m]);
		}
	}
	
	int b = 0;
	int e = s.size() - 1;
	for(int i = 1; i < s.size(); i++){
		if((i-b)%2 == 1){
			if(symmetric(b, i)){
				b = (i + b + 1) / 2;
				i = b;
			}
		}
	}
	for(int i = s.size() - 2; i >= b; i--){
		if((e-i)%2 == 1){
			if(symmetric(i, e)){
				e = (e + i) / 2;
				i = e;
			}
		}
	}
	
	cout << (e-b+1) << endl;
    
    return 0;
}

