/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/collatzconjecture
TAGS: gcd
EXPLANATION:
if we have the set of unique gcd's from i..j, we can get the set from i-1..j in
time linear to the size of the set.
new set is equal to the gcd of the new item and every previous set value, union with the new item. Works becuase of the way GCD cascades.
We also know the size of these sets is logarithmic, since every time a GCD changes, it is at least halved.
to generate all unique values of the function, we can just calculate all i..end starting at the end and moving towards the front.
N iterations, each taking log(10^18)^2 time. (1 log-time GCD function on a logarithmic amount of set values, so log^2)
overall Nlog^2(10^18)
END ANNOTATION
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll ints[500000];
int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i = 0;i<N;i++)
    {
    	cin >> ints[i];
    }
    unordered_set<ll> ans;
    unordered_set<ll> current;
    for(int i = N-1;i>=0;i--)
    {
    	unordered_set<ll> next;
    	for(ll x: current){
    		next.insert(__gcd(x, ints[i]));
    	}
    	next.insert(ints[i]);
    	current = next;
    	for(ll x: current){
    		ans.insert(x);
    	}
    }
    cout << ans.size();
}
