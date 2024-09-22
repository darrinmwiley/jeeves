/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/ninepacks
TAGS: dynamic programming, dp
EXPLANATION:
For the hotdogs and buns, make a list of the minimum cost to get a certain number. The cost of 0 is trivially 0.
For each pack size, look at all quantities that have already been given a cost. Find all quantities reachable from
them by adding the pack size. Set the cost of each new quantity to the cost of the first quantity plus 1 unless the new
quantity already has a cost that would be cheaper. Finally, find the quantity that has been reached for both hot dogs
and buns with the lowest sum of the cost for hot dogs and the cost for buns. If they have no common reached quantities,
it is impossible.
END ANNOTATION
*/
#include <iostream>
#include <vector>

using namespace std;

constexpr const unsigned UI_MAX = numeric_limits<unsigned>::max();

void getSums(const vector<unsigned>& packSizes, vector<unsigned>& netCosts)
{
	netCosts[0] = 0u;
	unsigned max = 1;
	for (unsigned packSize : packSizes)
	{
		for (unsigned i = max; i-- > 0;)
		{
			unsigned j = i + packSize;
			if (netCosts[i] != UI_MAX && (netCosts[j] == UI_MAX || netCosts[j] > netCosts[i] + 1))
				netCosts[j] = netCosts[i] + 1;
		}
		max += packSize;
	}
}

int main()
{
	unsigned H;
	cin >> H;
	unsigned hSumAll = 0;
	vector<unsigned> h(H);
	for (unsigned i = 0; i < H; i++)
	{
		cin >> h[i];
		hSumAll += h[i];
	}
	vector<unsigned> hSums(hSumAll + 1, UI_MAX);
	getSums(h, hSums);

	unsigned B;
	cin >> B;
	vector<unsigned> b(B);
	unsigned bSumAll = 0;
	for (unsigned j = 0; j < B; j++)
	{
		cin >> b[j];
		bSumAll += b[j];
	}
	vector<unsigned> bSums(bSumAll + 1, UI_MAX);
	getSums(b, bSums);

	unsigned minSumAll = min(hSumAll, bSumAll);

	unsigned best = UI_MAX;

	for (unsigned sum = 1; sum <= minSumAll; sum++)
	{
		unsigned hSum = hSums[sum], bSum = bSums[sum];
		if (hSum != UI_MAX && bSum != UI_MAX)
		{
			best = min(best, hSum + bSum);
		}
	}

	if (best == UI_MAX) cout << "impossible";
	else cout << best;

	return 0;
}