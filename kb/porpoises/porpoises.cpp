/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/porpoises
TAGS: dp, matrix exponentation
EXPLANATION:
* Starting from the matrix {{0, 1}, {1, 1}}, find its year-th power
* => result will be matrix[1][0]
* For more details on this technique: refer to this video: https://www.youtube.com/watch?v=eMXNWcbw75E
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define size(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printArray(arr) for (int i = 0; i<size(arr); i++) cout << arr[i] << " ";cout << '\n'
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
#define printDecimal(d) printf("%.9f\n", d)
#define inrange(val, start, end) (val >= start && val <= end)

const ll inf = 0x3f3f3f3f;
const int mod = 1e9;

template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) {cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n';}
template <class T1, class T2>
void printPair(pair<T1, T2> p) {cout << p.first << " " << p.second << '\n';}

vector<vector<ll>> multiply_matrix(vector<vector<ll>> a, vector<vector<ll>> b) {
	vector<vector<ll>> ret(2, vector<ll>(2, 0));
	for (int i = 0; i<2; i++) {
		for (int j = 0; j<2; j++) {
			for (int k = 0; k<2; k++) {
				ret[i][k] += a[i][j] * b[j][k];
				ret[i][k] %= mod;
			}
		}
	}
	return ret;
}

vector<vector<ll>> evaluate(ll n) {
	if (!n) return {{0, 0}, {0, 0}};
	if (n == 1) return {{0,1}, {1,1}};
	vector<vector<ll>> prev = evaluate(n/2), ret = multiply_matrix(prev, prev);
	if (n & 1) ret = multiply_matrix(ret, evaluate(1));
	return ret;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
    while (t--) {
        int cases; cin >> cases;
        ll year; cin >> year;
        vector<vector<ll>> ret = evaluate(year);
        cout << cases << " " << ret[1][0] << '\n';
    }
}

