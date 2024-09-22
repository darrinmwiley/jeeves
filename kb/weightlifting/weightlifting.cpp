/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/weightlifting
TAGS: Sequences, Dynamic Programming, DP, Optimization, Intervals
EXPLANATION:
In general, the different attempts the weightlifter could take for any s, the minimum score of 0, and the maximum strength of 225 divide the real line
into intervals. First, let us compute the number of intervals that we can create (excluding (-inf, 0) and (225, inf)). Let f(i) denote the number of
intervals that can be created with remaining energy i. Clearly, if i <= 0, we cannot do any more attempts, so we cannot divide the current interval further.
Thus, f(i) is 1 for i <= 0. If i > 0, we can do a test to divide the interval in half. Then, we can further subdivide the intervals to the left and right of
that test depending on the result. If the attempt was higher than s, we have i - e_failure energy left, so we subdivide the left interval into
f(i - e_failure) subintervals. If the attempt was lower than s, we have i - e_success energy left, so we subdivide the right interval into
f(i - e_success) subintervals. Thus, f(i) = f(i - e_failure) + f(i - e_success) if i > 0. The values of f can be computed by dynamic programming, storing
the values in an array and iteratively computing each value based on previous values. The values should be computed as doubles, for reasons that will be clear
later. Let n denote f(e).

Now, let us figure out how to optimally place the attempts to minimize d. For small n, as in sample 1 (where n == 2), it is best to evenly subdivide [0, 225]
into n intervals. If we were to evenly subdivide [25, 255] into n - 1 intervals, the intervals would be larger. However, once n > 9, this strategy generates
tests for weights less than 25, which is clearly suboptimal (a test at weight 25 would always be better). Thus, at that point, it is better to subdivide
[25, 225] into n - 1 intervals. When n == 9, these strategies are identical. Thus, 225 / n for n < 9 and 200 / (n - 1) for n >= 9 gives the correct answer.
n can be extremely large (up to a 2^10000000) and can easily overflow even a double. However, at that point, n will be rounded up to infinity and the formula
above will give an answer of 0. Since the correct answer is extremely small in these cases (at most about 10^-300), it fits easily within the required
precision of 10^-6.
END ANNOTATION
*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
	int e, es, ef;
	cin >> e >> es >> ef;
	vector<double> DP(e + 1, 1);
	for (int i = 1; i <= e; i++)
		DP[i] = DP[max(0, i - es)] + DP[max(0, i - ef)];
	cout << fixed << setprecision(7) << (DP[e] < 9 ? 225 / DP[e] : 200 / (DP[e] - 1));
}