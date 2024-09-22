/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/celebritysplit
TAGS:math, meet-in-middle
EXPLANATION: We split the mansions into two even sets. We are able to
* 				go over all 3^12 < 600000 possibilities for either giving
* 				Jack or Jill the mansion, or throwing it out. We keep track of
* 				Jack and Jills total, and we map the difference in the sums
* 				to the maximum corresponding total for Jack.
* 
* 				We then iterate over the second set, keeping track of the
* 				sums like last time. 
* 
* 				Using the difference map, we are able to find whether an 
* 				arrangement of the first set can come together with the second set
* 				to create an even sum
* 
* 				We keep the maximum possible sum, and take 2*max away from
* 				the sum of all mansions to find the value of the mansions
* 				thrown away.
* 
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

map<int, int> mp;
int arr[24];
int N;
int p3[15];

void process(){
	mp.clear();
	for(int i = 0; i < N; i++) cin >> arr[i];
	
	for(int i = 0; i < p3[N - N/2]; i++){
		int tmp = i;
		int s1 = 0, s2 = 0;
		for(int e = N/2; e < N; e++){
			int r = tmp%3;
			tmp /= 3;
			if(r == 0) s1 += arr[e];
			else if(r == 1) s2 += arr[e];
		}
		if(!mp.count(s2-s1) || (s1 > mp[s2-s1])) mp[s2-s1] = s1;
	}
	
	int ans = 0;
	for(int i = 0; i < p3[N/2]; i++){
		int tmp = i;
		int s1 = 0, s2 = 0, ns = 0;
		for(int e = 0; e < N/2; e++){
			int r = tmp%3;
			tmp /= 3;
			if(r == 0) s1 += arr[e];
			else if(r == 1) s2 += arr[e];
			else ns += arr[e];
		}
		
		if(mp.count(s1 - s2)){
			ans = max(ans, s1 + mp[s1-s2]);
		}
	}
	
	int s = 0;
	for(int i = 0; i < N; i++) s += arr[i];
	cout << (s-(2*ans)) << endl;
}

int main(){
	p3[0] = 1;
	for(int i = 1; i < 15; i++) p3[i] = 3*p3[i-1];
	cin >> N;
	while(N != 0) {
		process();
		cin >> N;
	}
	
	return 0;
}
