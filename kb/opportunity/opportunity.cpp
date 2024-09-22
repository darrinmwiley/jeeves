/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/opportunity
TAGS: math
EXPLANATION: We take the sums of all 8 subsets of x, y, and z
* 				The opportunity cost is the maximum difference of one
* 				of these subsets to a corresponding subset of another phone
* 				For each possible subset, we keep track of the max value among
* 				all phones, so we can quickly get the opportunity cost
* 				for each phone
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

int N;
int v[200000][3];
ll sums[8] = {0};

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
		cin >> v[i][0] >> v[i][1] >> v[i][2];
		for(int e = 0; e < 8; e++){
			ll s = 0;
			for(int l = 0; l < 3; l++){
				if((e >> l) & 1) s += v[i][l];
			}
			sums[e] = max(sums[e], s);
		}
	}
    
    ll ans = 1000000000;
    int ind = -1;
    for(int i = 0; i < N; i++){
		ll mx = 0;
		for(int e = 0; e < 8; e++){
			ll s = 0;
			for(int l = 0; l < 3; l++){
				if((e >> l) & 1) s += v[i][l];
			}
			mx = max(mx, sums[e] - s);
		}
		//cout << i << " " << mx << endl;
		if(mx < ans){
			ans = mx;
			ind = i;
		}
	}
	
	cout << ans << " " << (ind+1) << endl;
    
    return 0;
}
