/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/sequences
TAGS: sequences, inversions, sorting, modular
EXPLANATION:
It is a well-known fact that the number of adjacent swaps required to sort an array is equal to the number of out-of-order
pairs of elements. This is easily demonstrated by the fact that bubble sort, which performs the optimal number of adjacent
swaps necessary to sort an array, obviously reduces the number of remaining adjacent swaps every time it swaps a pair of
elements, and furthermore, that each of these adjacent swaps reduces the number of pairs of out-or-order elements by one.
In order to count the total number of inversions, one can count the number of inversions formed by a pair of the form 1-0
(I10), the number of inversions of the form ?-0 (IQ0), the number of inversions of the form 1-? (I1Q), and the number of
inversions of the form ?-? (IQQ). The result is I10 + IQ0 + I1Q + IQQ.

To calculate I10, we first must find the number of inversions in the list omitting ?'s. This can be done by iterating through
the list, keeping a running count of 1's (ct1) and of 1-0 inversions (ct10). Simply add 1 to ct1 each time 1 is encountered
and add ct1 to ct10 each time 0 is encountered (as 0 forms a 1-0 inversion with each 1 previously encountered). Multiplying
ct10 by the number of sequences considered (2^k) gives us I10.

To calculate IQ0 and I1Q, we interate through the sequence (this can be done simultaneously with I10's calculation), keeping
a running count of 1's (ct1) and ?'s (ctQ) encountered, as well as a running count of inversions of the form ?-0 or 1-?
(ctQ0_1Q). ct1 is computed as before, and each time a ? is encountered, ctQ is incremented. Furthermore, each time a 0
is encountered, ctQ0_1Q is incremented by ctQ, and each time a ? is encountered, ctQ0_1Q is incremented by ct1. Each of these
encountered inversions only count as "half" of an inversion, as the ? will ony have the correct value to form the inversion
half of the time, so IQ0 + I1Q can be computed as ctQ0_1Q*2^(k-1).

To calculate IQQ, consider the sequence consisting only of k ?'s (remove all 0's and 1's); this can represent any of the 2^k
0-1 sequences of length k. Half of the sequence elements are 0's, so the total number of 0's in all such sequences is
k*2^(k-1). Each set of sequences of length k+1 can be constructed as the set of sequences of length k with a 0 prepended
combined with the set of sequences of length k with a 1 prepended. The number of inversions when 0 is prepended is IQQ(k),
as the leading 0 does not form any new inversions, and the number of inversions when 1 is prepended is IQQ(k) + k*2^(k-1),
as the leading 1 forms an inversion with each 0 in the original set of length-k sequences. IQQ(0) = 0, since the empty
sequence contains no inversions, and IQQ(k+1) = 2*IQQ(k) + k*2^(k-1), giving us a recursive definition of IQQ(k). We can show
that IQQ(k) = (k*(k-1))/2 * 2^(k-1) * 2^-1 using induction; see https://oeis.org/A001788 for more details about this function.
We can use the multiplicative inverse of 2 mod 1000000007 as 2^-1 to guarantee an integer result (as 2^(k-1) mod 1000000007 may
be odd even for k > 1). Summing these formulas, being careful to take intermediate results mod 1000000007 to avoid overflow,
gives us the result.
END ANNOTATION
*/

#include <iostream>

constexpr const unsigned long long int MOD = 1000000007;
// The multiplicative inverse of 2 mod 1000000007. Note that the multiplicative
// inverse of 2 mod m is always (m+1)/2 if m is odd and m >= 3.
constexpr const unsigned long long int INV2 = (MOD + 1) / 2;

int main()
{
	// Sets up fast I/O
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	// Running count of 1's
	unsigned long long int ct1 = 0;
	// Running count of ?'s;
	unsigned long long int ctQ = 0;
	// Running count of 1-0 inversions
	unsigned long long int ct10 = 0;
	// Running count of ?-0 and 0-? inversions
	unsigned long long int ctQ0_1Q = 0;

	char ch;
	while (!std::cin.eof() && std::cin >> ch)
	{
		switch (ch)
		{
		case '0':
			ct10 = (ct10 + ct1) % MOD;
			ctQ0_1Q = (ctQ0_1Q + ctQ) % MOD;
			break;
		case '1':
			ct1++;
			break;
		case '?':
			ctQ0_1Q = (ctQ0_1Q + ct1) % MOD;
			ctQ++;
			break;
		}
	}

	// These could exceed 2^32; this keeps them in a reasonable range.
	ct10 %= MOD;
	ctQ0_1Q %= MOD;

	// If there are no question marks, there is only one sequence to consider (which is the given sequence)
	// and its inversions are all 1-0 inversions.
	if (ctQ == 0)
	{
		std::cout << ct10;
		return 0;
	}

	// Initially q-1
	unsigned long long int qm1 = ctQ - 1;
	// Will be 2^(q-1)
	unsigned long long int pow2qm1 = 1;
	unsigned long long int mul = 2;

	// Binary exponentiation (although regular exponentiation should be fast enough for this problem)
	while (qm1 > 0)
	{
		if (qm1 % 2 == 1)
		{
			pow2qm1 = (pow2qm1 * mul) % MOD;
		}
		mul = (mul * mul) % MOD;
		qm1 /= 2;
	}

	// I10 mod 1000000007
	unsigned long long int sum10 = ct10 * pow2qm1 % MOD * 2 % MOD;
	// (IQ0 + I1Q) mod 1000000007
	unsigned long long int sumQ0_1Q = ctQ0_1Q * pow2qm1 % MOD;
	// IQQ mod 1000000007
	unsigned long long int sumQQ = ctQ * (ctQ - 1) / 2 % MOD * pow2qm1 % MOD * INV2 % MOD;

	std::cout << (sum10 + sumQ0_1Q + sumQQ) % MOD;

	return 0;
}