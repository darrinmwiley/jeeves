/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/brackets
TAGS: parenthesis matching, dynamic programming, prefix sums, brute force
EXPLANATION:
The first thing to notice about this problem is its small maximum input size of 5000. This means that there are somewhere around
5000^2/2 = 1.25e+7 possible ranges. Thus, we have enough time to brute force all possible ranges, but each range needs to be tested
in O(1) time (even Theta(lg n) per iteration is probably too slow). Thus, we need a fast way to test whether a given range solves the
problem with at most O(n^2) precomputation time.

In order to determine whether a sequence of parentheses are valid, first assign each ( a value of +1 and each ) a value of -1. This
means that the sum over a range of parentheses will be positive iff there are excess ('s, negative iff there are excess )'s, and 0 iff
there are the same number of ('s and )'s. Also, note that if the sum over a range is 0, the minimum of the prefix sums of that range
will be negative iff there are pairs of parentheses that cannot be matched because they are in the wrong order. These conditions turn
out to be sufficient for testing a valid bracket sequence. Thus, all we need is an O(1) method for computing these values after one
segment inversion.

Inverting segment [l, r] corresponds to negating all of the values in that range. The sum of that range is also negated. Normally,
the sum over the entire sequence can be computed as Sum([1 : l - 1]) + Sum([l : r]) + Sum([r + 1 : n]), where Sum([i : j]) refers to
the sum over the subsequence with indices ranging from i to j (inclusive). After the inversion, this becomes
Sum([1 : l - 1]) - Sum([l : r]) + Sum([r + 1 : n]). Computing the minimum prefix sum over this range is slightly more complicated. Let
Min([i : j]) and Max([i : j]) refer to the minimum and the maximum, respectively, of all values Sum([i : k]) for i <= k <= j. If the
minimum prefix sum occurs before the inverted range, the minimum prefix sum is just Min([1 : l - 1]). If it occurs inside the inverted
range, the minimum prefix sum is Sum([1 : l - 1]) - Max([l : r]). If it occurs after the inverted range, the minimum prefix sum is
Sum([1 : l - 1]) - Sum([l : r]) + Min([r + 1 : n]). Inverting [l : r] thus produces a valid subsequence iff the minimum of these three
values is nonnegative and the aforementioned sum is 0.

In order for this to be efficient enough, we must be able to compute the sum, min-sum, and max-sum of any range in O(1) time. Normally,
this would be solved by constructing prefix sums over the values and two sparse tables over those prefix sums. However, since we are
already brute forcing every possible range, precomputing every range's sum, min-sum, and max-sum in O(n^2) time works. Be sure to use
dynamic programming when constructing these tables by building every row as you would a prefix sum array. Otherwise, this will
degenerate to an O(n^3) algorithm. Also, remember to also check for the case where the sequence is already valid.
END ANNOTATION
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> A;
	char ch;
	while (cin >> ch)
		A.push_back(ch == '(' ? 1 : -1);
	int n = A.size();

	vector<vector<int>> Sum(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
	{
		Sum[i][i] = A[i];
		for (int j = i + 1; j < n; j++)
			Sum[i][j] = Sum[i][j - 1] + A[j];
	}

	vector<vector<int>> Min(n, vector<int>(n, 0));
	vector<vector<int>> Max(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
	{
		Min[i][i] = Max[i][i] = A[i];
		for (int j = i + 1; j < n; j++)
		{
			Min[i][j] = min(Min[i][j - 1], Sum[i][j]);
			Max[i][j] = max(Max[i][j - 1], Sum[i][j]);
		}
	}

	if (Sum[0][n - 1] == 0 && Min[0][n - 1] >= 0)
	{
		cout << "possible";
		return 0;
	}

	for (int l = 0; l < n; l++)
		for (int r = l; r < n; r++)
		{
			int sum1 = l == 0 ? 0 : Sum[0][l - 1];
			int sum2 = Sum[l][r];
			int sum3 = r == n - 1 ? 0 : Sum[r + 1][n - 1];
			int min1 = l == 0 ? 0 : Min[0][l - 1];
			int max2 = Max[l][r];
			int min3 = r == n - 1 ? 0 : Min[r + 1][n - 1];
			if (sum1 - sum2 + sum3 == 0 && min1 >= 0 && sum1 - max2 >= 0 && sum1 - sum2 + min3 >= 0)
			{
				cout << "possible";
				return 0;
			}
		}

	cout << "impossible";
}