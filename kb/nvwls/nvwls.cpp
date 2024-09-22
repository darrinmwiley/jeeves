/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/nvwls
TAGS: hashing
EXPLANATION:
We turn every dictionary word into only its consonants, hash it, so store the hash, along with the number of vowels
We can use a rolling hash for a dp, where dp[i] is the max amount of vowels that can be done in a translation
To find dp[i], we check all possible lengths l, and if the corrseponding suffix is in the dictionary, then use dp[i-l] to
update dp[i].
This runs in time because there is only a maximum of sqrt(N) possible lengths, running in O(Nsqrt(N))

END ANNOTATION
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <assert.h>

using namespace std;

map<int, int> lens;
map<int, int> dict[1000];
map<int, string> rhsh[1000];
int hsh[300001];
int p27[300001];
int dp[300001];
int lst[300001];
int llen[300001];
int pre[300001];

int MOD = 1000000007;

int mult(int a, int b) {
	return (int)((long long)a*b%MOD);
}
int ad(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}

bool vowel(char c) {
	return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void addWords(string s) {
	int v = 0;
	int c = s.size();
	int h = 0;
	for (int i = 0; i < s.size(); i++) {
		if (vowel(s[i])) {
			v++;
			c--;
			continue;
		}
		h = mult(h, 27);
		h = ad(h, s[i] - 'A' + 1);
	}
	if (!lens.count(c)) {
		int ind = lens.size();
		lens[c] = ind;
	}
	int ind = lens[c];
	if (!dict[ind].count(h) || v > dict[ind][h]) {
		dict[ind][h] = v;
		rhsh[ind][h] = s;
	}
}

int getSub(int r, int len) {
	int l = r - len;
	int res = hsh[r] - mult(hsh[l], p27[len]);
	if (res < 0) res += MOD;
	return res;
}

int main()
{
	p27[0] = 1;
	for (int i = 1; i <= 300000; i++) {
		p27[i] = mult(p27[i - 1], 27);
	}
	int D;
	cin >> D;
	for (int i = 0; i < D; i++) {
		string s;
		cin >> s;
		addWords(s);
	}

	string s;
	cin >> s;
	hsh[0] = 0;
	dp[0] = 0;
	for (int i = 1; i <= s.size(); i++) {
		dp[i] = -1;
		hsh[i] = mult(hsh[i - 1], 27);
		hsh[i] = ad(hsh[i], s[i-1] - 'A' + 1);

		for (auto p : lens) {
			if (dp[i - p.first] == -1) continue;
			if (p.first > i) continue;
			int hshSub = getSub(i, p.first);
			if (dict[p.second].count(hshSub)) {
				int tmp = dp[i - p.first] + dict[p.second][hshSub];
				if (tmp > dp[i]) {
					dp[i] = tmp;
					lst[i] = hshSub;
					llen[i] = p.second;
					pre[i] = i - p.first;
				}
			}
		}
	}

	vector<int> res;
	vector<int> resl;
	int i = s.size();
	while (i > 0) {
		res.push_back(lst[i]);
		resl.push_back(llen[i]);
		i = pre[i];
	}
	while (!res.empty()) {
		cout << rhsh[resl.back()][res.back()] << " ";
		res.pop_back();
		resl.pop_back();
	}
	cout << endl;

	return 0;
}