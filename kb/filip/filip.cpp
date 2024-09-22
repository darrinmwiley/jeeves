/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/filip
TAGS: easy
EXPLANATION:
read in strings, reverse, parse, compare
END ANNOTATION
*/
#include "bits/stdc++.h"

using namespace std;

#define pb push_back
#define boolean bool
#define li long long int

string A, B;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> A >> B;
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	int AA = stoi(A);
	int BB = stoi(B);
	cout << max(AA,BB) << endl;
}
