/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/virtualfriends
TAGS:union-find
EXPLANATION: Goes through input to note the names and matches them to indexes.
* 				Then goes through again to merge friends and uses rank to 
* 				tell size of network
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
pii friends[100000];
map<string, int> mp;
int par[100000];
int rk[100000];

int find(int a){
	if(a != par[a])
		return par[a] = find(par[a]);
	return a;
}

void merge(int a, int b){
	a = find(a);
	b = find(b);
	if(a == b) return;
	par[a] = b;
	rk[b] += rk[a];
}

void process(){
	mp.clear();
	cin >> N;
	for(int i = 0; i < N; i++){
		string s1, s2;
		cin >> s1 >> s2;
		if(!mp.count(s1)) {
			int m = mp.size();
			mp[s1] = m;
		}
		if(!mp.count(s2)) {
			int m = mp.size();
			mp[s2] = m;
		}
		friends[i].first = mp[s1];
		friends[i].second = mp[s2];
	}
	
	for(int i = 0; i < mp.size(); i++) {
		par[i] = i;
		rk[i] = 1;
	}
	for(int i = 0; i < N; i++){
		merge(friends[i].first, friends[i].second);
		cout << rk[find(friends[i].first)] << endl;
	}
}

int main(){
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++){
		process();
	}
	return 0;
}
