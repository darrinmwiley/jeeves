/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/perica
TAGS: combinatorics
EXPLANATION:
If an element has m elements below it, there are (m choose K-1) possible combinations 
such that the element is the maximum in the combination. If we sort the list, we can 
iterate over every possible maximum element. We then multiply the number of combinations
by the value and add it to the answer.

END ANNOTATION
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int N, K;
int MOD = 1000000007;
int fct[100001];
int ifct[100001];
int arr[100000];

int mult(int a, int b) {
	return (int)((long long)a*b%MOD);
}
int ad(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}
int exp(int a, int b) {
	int res = 1;
	while (b > 0) {
		if (b % 2) res = mult(res, a);
		b /= 2;
		a = mult(a, a);
	}
	return res;
}
int modInv(int a) {
	return exp(a, MOD - 2);
}
int comb(int a, int b) {
	return mult(fct[a], mult(ifct[b], ifct[a - b]));
}

int main()
{
	fct[0] = 1;
	ifct[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		fct[i] = mult(i, fct[i - 1]);
		ifct[i] = modInv(fct[i]);
	}

	cin >> N >> K;
	for (int i = 0; i < N; i++) cin >> arr[i];
	sort(arr, arr + N);

	

	int ans = 0;
	for (int i = K-1; i < N; i++) {
		ans = ad(ans, mult(arr[i], comb(i, K - 1)));
	}
	cout << ans << endl;

	return 0;
}