/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/lottery
TAGS: math, binomial, coefficient, coefficients, binomial coefficient, binomial coefficients, sum, number, theory, number theory
EXPLANATION:
In order to solve this problem, we first need to find a formula for the probability that the number of winners in our group is equal
to a given number (henceforth referred to as d). There are nCr(p, d) ways to choose the d winners from the p group members and
nCr(m - p, n - d) ways to choose the n - d winners from the m - p people outside the group. Thus, there are nCr(p, d) * nCr(m - p, n - d)
ways to choose winners such that d of them are in our group, out of a total of nCr(m, n) ways to choose the n winners from all m people.
Thus, the problem reduces to summing nCr(p, d) * nCr(m - p, n - d) over all values of d such that at least p tickets are won by group
members and dividing the result by nCr(m, n). Note that the value of the numerator cannot exceed nCr(m, n), as the result is a
probability and cannot exceed 1. (This can also be seen from Vandermonde's Identity.) The value of the denominator cannot exceed
nCr(1000, 500), which is less than 10^301 and thus fits in a double. Therefore, if values of nCr are precomputed using Pascal's Triangle,
no overflow will occur. There are enough tickets held by group members to cover the entire group iff d * t >= p. Since d is an integer,
that is equivalent to d >= ceil(p / t), or equivalently, d >= floor((p + t - 1) / t). Additionally, the number of winners in the group
cannot exceed the group's size (d <= p) or the total number of winners (d <= n), and the number of winners outside the group cannot
exceed the number of people outside the group (n - d <= m - p, or equivalently, d >= n + p - m). Therefore, summing the above formula
for all values of d from max(floor((p + t - 1) / t), n + p - m) to min(n, p), inclusive, gives the correct answer.
END ANNOTATION
*/

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// Computes Pascal's triangle, which contains the binomial coefficients.
	vector<vector<double>> nCr;
	nCr.reserve(1001);
	for (int i = 0; i <= 1000; i++)
	{
		nCr.emplace_back(i + 1);
		nCr[i][0] = 1;
		nCr[i][i] = 1;
		for (int j = 1; j < i; j++)
			nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
	}

	int m, n, t, p;
	cin >> m >> n >> t >> p;

	int minD = max((p + t - 1) / t, n + p - m), maxD = min(n, p);
	double ans = 0;
	for (int d = minD; d <= maxD; d++)
		ans += nCr[p][d] * nCr[m - p][n - d];
	cout << fixed << setprecision(10) << ans / nCr[m][n];
}