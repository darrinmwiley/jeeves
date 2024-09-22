/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/accesspoints
TAGS: geometry, distance, points, stack, greedy, average, mean
EXPLANATION:
First, note that due to the Pythagorean Theorem, the sum of squared distances is equal to the sum of total squared differences
in each dimension. Due to this fact, as well as the fact that the monotonicity constraint is per-dimension, the problem can
simply be solved independently for each dimension; the final result is just the sum of those solutions.

For a given dimension, the optimal solution can be seen as a sequence of ranges of consecutive teams, where each range consists of
elements with the same coordinate. It is easy to see that the monotonicity constraint also applies to the averages of these ranges.
For a given range, the question that naturally arises is what coordinate is the optimal position for those teams to be? This is
clearly the position that minimizes the sum of squared differences between itself and each access point coordinate in the range.
Conveniently, this is simply the mean of the access point coordinates (which can be seen by taking the derivatives of the squared
differences and solving for where their sum vanishes). Thus, the following algorithm gives the correct answer for the 1D case:

Maintain a stack of ranges, where each range is represented by the sum of its elements and the number of elements. The mean of a
range can be computed by dividing these two values. Iterating backwards over the set of teams, first construct a trivial range
consisting only of the current team located at its access point. Then, if there is a range on top of the stack that would violate the
monotonicity constraint with, or has the same mean as, the current range (i.e. the current range's mean is greater than or equal to that
of the top of the stack), merge them (by adding the sum and element count of the range on the stack to the current range)and pop from
the stack. Continue this process of merging and popping as long as there remains a suitable range on top of the stack. After iterating
over all teams, the stack contains a partition of the teams into ranges, where each range's average is the optimal coordinate for each of
its teams. Then, simply store each team's coordinate and sum the squared differences bewteen them and the access point coordinates.

Each step of this algorithm runs in constant amortized time because each merge and pop can be charged to the first element of the popped
range. The overall algorithm then runs in linear time with respect to the number of input coordinates.
END ANNOTATION
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

struct Range
{
	double sum;
	int weight;

	inline Range(double sum, int weight) :
		sum(sum), weight(weight)
	{}

	inline Range(double sum) :
		Range(sum, 1)
	{}

	inline Range() :
		Range(0, 0)
	{}

	double value() const noexcept
	{
		return sum / weight;
	}
};

double solve1D(const vector<double>& S)
{
	int n = S.size();
	vector<Range> R;
	R.reserve(n);
	for (int i = n; i-- > 0;)
	{
		Range c(S[i]);
		while (!R.empty() && c.value() >= R.back().value())
		{
			c.sum += R.back().sum;
			c.weight += R.back().weight;
			R.pop_back();
		}
		R.push_back(c);
	}
	vector<double> X;
	X.reserve(n);
	for (const Range& r : R)
	{
		double x = r.value();
		for (int i = 0; i < r.weight; i++)
			X.push_back(x);
	}
	reverse(X.begin(), X.end());
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		double d = S[i] - X[i];
		ans += d * d;
	}
	return ans;
}

int main()
{
	int n;
	cin >> n;
	vector<double> S(n), T(n);
	for (int i = 0; i < n; i++) cin >> S[i] >> T[i];
	cout << fixed << setprecision(7) << solve1D(S) + solve1D(T);
}