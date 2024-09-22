/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/monkey
TAGS:union-find
EXPLANATION: If you wanted to carry all the smoothie to another location,
* 				this would take ceiling(W/C) trips. However, once the weight
* 				goes down, the number of trips reduces. 
* 				Let t = ceiling(W/C). The smoothie removed is t*distance, 
* 				so we can choose to move all the smoothie a certain distance, 
* 				such that when we are done moving it, the remaining smoothie 
* 				is the next multiple of C. 
* 				We can keep doing this until the distance is short enough 
* 				for us to just take as much smoothie as possible and move 
* 				it to the end.
* 
* 				For the purposes of implementation, I represented W as k*C + r
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

double f(double d, int k, int r, int c){
	if(r == 0){
		if(k == 1){
			if(d > c) return 0.0;
			return (c - d);
		}
		if(d * (2*k - 1) < c){
			return (k*c - (2*k - 1)*d);
		}
		return f(d - (double)c / (2*k - 1), k-1, r, c);
	}
	if(k == 0){
		if(d > r) return 0.0;
		return (r - d);
	}
	if(d*(2*k + 1) < r){
		return (k*c + r - (2*k + 1)*d);
	}
	return f(d - (double) r / (2*k + 1), k, 0, c);
}

int main(){
	cout << fixed << setprecision(7);
	int D, W, C;
	cin >> D >> W >> C;
	double ans = f(D, W/C, W%C, C);
	cout << ans << endl;
	
	return 0;
}
