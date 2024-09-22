/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/kralj
TAGS: cycle, shift, successor, circular, greedy, matching
EXPLANATION:
This problem can be solved by reducing it to the special case where no elf walks from dwarf N to dwarf 1. This can be done by considering
the number of elves that must walk from the previous dwarf to the current dwarf. For each dwarf i, let I[i] be the number of elves
directly attacking them and K[i] be the number of elves that walk to them from the previous dwarf. The total number of elves that walk
in front of dwarf i at some point is K[i] + I[i] (as each such elf must either walk to the current dwarf or directly try to attack it).
One of these elves will sit down in front of dwarf i, leaving the remaining K[i] + I[i] - 1 = K[(i + 1) % N] elves to continue walking
to dwarf (i + 1) % N. Computing I is trivial, so given the value of K[1], all other values of K can be computed. Observe that the
following statements must hold:

1) All values of K are nonnegative. As long as the previous dwarf has at least one elf walk or sit in front of it, dwarf i will have a
   nonnegative K value. This is because the number of such elves is equal to the sum of K and I values for the previous dwarf.
   Subtracting 1 from this gives the current K value. As there are the same number of dwarves as elves, each dwarf ends up with one elf
   sitting in front of them, so this condition is met for all dwarves.

2) At least one dwarf has a K value of 0. In particular, for some arbitrary order in which the elves enter the hall, the last dwarf to
   receive an elf does not pass any elves to the next dwarf. Thus, that next dwarf has a K value of 0.

These observations lead to the conclusion that the dwarf with the minimum K value must not receive an elf from the previous dwarf.
Circularly shifting the dwarves (by updating A and rotating P) such that this dwarf is in position 1 results in a problem with
the same answer as the original with the additional property that no elves pass from dwarf N to dwarf 1. Thus, the dwarves can be
thought of as a line instead of a circle. However, computing this shift requires one to find the minimum value of K. Luckily, the
formula for K values still works if all K values are shifted by the same amount. Thus, for the purpose of finding the minumum, K[1] can
be set to any value, and the formula can be used to compute all other K values.

Once this reduction is done, the problem comes down to figuring out which elf to use to fight which dwarf. First, assign to each dwarf
a (possibly empty) list of all elves that start in front of it. Maintain a set of elves (specifically, an ordered set of values from V)
that could end up sitting in front of the current dwarf (which is initially empty). For each dwarf, first add the strengths of all elves
that start in front of it to this list. Then, select the optimal elf to fight the current dwarf. If there are elves that are stronger
than this dwarf, choose the weakest such elf (the successor to the dwarf's strength in the set). Otherwise, choose the weakest remaining
elf. Then, remove that elf from the set. Following this approach, Slavko gets victories wherever possible and keeps the strongest elves
possible for future dwarves. The answer is simply the number of selected elves that were stronger than their dwarves.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
	int N;
	cin >> N;
	vector<int> A(N), P(N), V(N);
	for (int i = 0; i < N; i++) cin >> A[i], A[i]--;
	for (int i = 0; i < N; i++) cin >> P[i];
	for (int i = 0; i < N; i++) cin >> V[i];

	vector<int> I(N, 0);
	for (int a : A) I[a]++;

	// Reduction to non-circular list of dwarves
	// N is greater than any possible k value.
	int k = 0, minK = 0, mindex = 0;
	for (int i = 1; i < N; i++)
	{
		k = k + I[i - 1] - 1;
		if (k < minK)
		{
			minK = k;
			mindex = i;
		}
	}
	// Perform the cyclic shift
	for (int& a : A) a = (a + N - mindex) % N;
	rotate(P.begin(), P.begin() + mindex, P.end());

	// Lists of elves mapping to each dwarf.
	vector<vector<int>> B(N);
	for (int i = 0; i < N; i++) B[A[i]].push_back(i);
	// Set of currently usable elf strengths.
	set<int> S;
	// Running count of winning elves.
	int ans = 0;
	for (int i = 0; i < N; i++)
	{
		for (int b : B[i]) S.insert(V[b]);
		set<int>::const_iterator iter = S.upper_bound(P[i]);
		if (iter == S.cend())
			iter = S.cbegin();
		else
			ans++;
		S.erase(iter);
	}
	cout << ans;
}