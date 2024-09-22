/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/bestrational
TAGS: math, binary search
EXPLANATION: 
* To solve this I used the Farey sequence
* https://en.wikipedia.org/wiki/Farey_sequence
* 
* The Farey sequence of order n is the ordered list of all rational a/b such that b <= n
* One property of these is that if a/b, p/q, and c/d are consecutive in a sequence of any order,
* then p/q = (a+c)/(b+d). This allows us to do a sort of binary search over rational fractions.
* Everything else is math to compare rational numbers. I needed int128 and I don't know if
* there is a solution without it.
END ANNOTATION
*/

//Suraj Mathashery

#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <iomanip>
#include <string>

using namespace std;


typedef long long ll;
typedef __int128_t i128;
i128 p10 = (i128)1e18;

void process(){
	int M;
	string s;
	cin >> M;
	cin >> s;
	if(s.size() < 2 || s[1] != '.'){
		cout << "0/1\n";
		return;
	}
	s = s.substr(2);
	while(s.size() < 18) s.append("0");
	i128 f = (i128)stoll(s);
	
	i128 bn = 0, bd = 1, en = 1, ed = 1;
	
	while(ed <= M && bd <= M){
		i128 mn = bn+en;
		i128 md = bd+ed;
		if(md > M) break;
		if(mn*p10 < md*f){
			bn = mn;
			bd = md;
		}
		else{
			en = mn;
			ed = md;
		}
	}
	
	if(2*f*ed*bd < p10*en*bd + p10*bn*ed){
		cout << (int)bn << "/" << (int)bd << endl;
	}
	else
		cout << (int)en << "/" << (int)ed << endl;
}

int main(){
	int N;
	cin >> N;
	for(int i = 0; i < N; i++){
		int x;
		cin >> x;
		cout << x << " ";
		process();
	}
	
	return 0;
}
