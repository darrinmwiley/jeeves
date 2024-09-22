/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/communicatingstrategy
TAGS: Math, Combinatorics, Recursion, Recurrences, Modular, Modular Arithmetic, Modular Inverse, Interactive
EXPLANATION:
Let us try to solve this problem using a sequence of queries over the ranges [1, r] for each r in [1, n]. Note that
the total weight is the sum of 1/r^2 over r in [1, n], which is less than that sum over [1, inf). The sum of the
reciprocals of the squares converges to pi^2/6 < 5/3, so the weight constraint is not an issue for this strategy regardless
of n.

Now, let P(B) be the product of all elements of S (mod M), Ar be the array [a1, a2, ..., ar], and
f(k, r) be the sum of P(B) over all subsets B of Ar with cardinality k. If k is 0, there is only 1 such set. It has no
elements, so its product is 1. Thus, f(0, r) == 1. Furthermore, k < 0 or k > r is impossible, so in those cases, f is 0.

For other values of f, consider some subset B of Ar. Notice that ar can either be in B or not. In the former case, B is also
a subset of A(r-1) and |B| == k, so P(B) contributes to f(k, r - 1). In the latter case, let B' := B \ {ar} (B with ar removed).
Then, B' is a subset of A(r-1) and |B'| == k - 1, so P(B') contributes to f(k - 1, r - 1) and P(B) == P(B') * ar. This gives
the recurrence f(k, r) == f(k, r - 1) + ar * f(k - 1, r - 1) (mod M), where the left side of the + corresponds to sets not
containing ar and the right side of the + corresponds to sets containing r. For the query "1 1 r", we are given k in [1, r]
and S = f(k, r). Rearranging the recurrence, we get that ar * f(k - 1, r - 1) == S - f(k, r - 1). Thus, we can compute
ar as (S - f(k, r - 1)) * f(k - 1, r - 1)^-1 (mod M), where ^-1 is the modular multiplicative inverse (a^-1 mod M can
be computed as a^(M - 2) mod M using binary exponentiation for prime M). If this procedure is iterated, when processing
query "1 1 r", we already know ai for all i in [0, r), which is enough to determine ar using the above recurrence recursively.
Adding memoization, this approach is easily fast enough for n <= 100.
END ANNOTATION
*/

#include <vector>
#include <iostream>
#include <tuple>
#include <unordered_map>

using namespace std;

constexpr int64_t MOD = 1e9 + 7;

// inverse mod 1e9+7
inline int64_t inv(int64_t n)
{
	int64_t ans = 1;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	ans = ans * ans % MOD;
	ans = ans * ans % MOD * n % MOD;
	return ans;
}

template<class T, class U>
struct std::hash<pair<T, U>>
{
	size_t inline constexpr operator()(const pair<T, U>& p) const noexcept
	{
		return hash<T>()(p.first) * 31 + hash<U>()(p.second);
	}
};

vector<int64_t> A;
unordered_map<pair<int, int>, int64_t> DP;

inline int64_t f(int k, int r)
{
	if (k == 0)
		return 1;
	if (k > r || k < 0)
		return 0;

	pair<int, int> kr(k, r);

	if (DP.find(kr) != DP.end())
		return DP[kr];
	else
		return DP[kr] = (f(k, r - 1) + A[r - 1] * f(k - 1, r - 1)) % MOD;
}

int main()
{
	int n;
	cin >> n;
	A.resize(n);

	for (int r = 1; r <= n; r++)
	{
		cout << "1 1 " << r << endl;
		int k;
		cin >> k;
		pair<int, int> kr(k, r);
		cin >> DP[kr];
		A[r - 1] = (f(k, r) - f(k, r - 1) + MOD) % MOD * inv(f(k - 1, r - 1)) % MOD;
	}

	cout << 2;
	for (int64_t a : A)
		cout << ' ' << a;
}