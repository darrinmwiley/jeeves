/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/gigcombinatorics
TAGS: combinatorics, sequence
EXPLANATION:
For each (1, 3) pair, call the number of 2's between them x. (This was referred to as f3i - f1j in Dr. Chitturi's meeting on this problem.) The number of setlists for this pair is 2^x-1, as each 2 may either be included or excluded (2^x) and the situation with no 2's is not allowed (-1). The sum of 2^x at each point in the list can be calculated by starting at 0 and iterating through the list. If 1 is encountered, add 1 to the running total, and if 2 is encountered, double it. Encountering a 2 should increase each x by 1. This is equivalent to doubling each 2^x, which is equivalent to doubling the whole sum of all 2^x's. Encountering a 1 means we should add a new 2^x to the sum, where x = 0 (as no 2's have yet been encountered). Upon reaching a 3, the total number of setlists for all (1, 3) pairs ending with that 3 can be computed as a - b, where a is the running sum of 2^x and b is the number of 1's encounterd so far. The -b corresponds to subtracting 1 from each of the 2^x's. Keeping a running sum of a - b at each 3 then gives us the sum of 2^x - 1 for all (1, 3) pairs, which is the answer. Of course, all operations should be done mod p.

To recap for each digit:
 - Encountering 1 increments a, as we have to keep track of a new value of 2^x in the sum (with x initially equal to 0). It also increments b, the running count of 1's encountered.
 - Encountering 2 doubles a, as each setlist started so far has the possibility of either including this song or not including it.
 - Encountering 3 means we must add 2^x-1 to the result for all (1, 3) pairs ending with that 3. a already contains the sum of 2^x and -b is the sum of the -1's. Thus, the formula would be c += a - b, although to account for mod p, it is instead c = (c + a + p - b) % p.
END ANNOTATION
*/

#include <iostream>

const unsigned p = 1000000007;
int main()
{
	unsigned n;
	std::cin >> n;
	char d;
	unsigned a = 0;
	unsigned b = 0;
	unsigned c = 0;
	for(unsigned i = 0; i < n; i++)
	{
		std::cin >> d;
		switch (d)
		{
		case '1':
			a = (a + 1) % p;
			b++;
			break;
		case '2':
			a = (a * 2) % p;
			break;
		case '3':
			c = (c + a + p - b) % p;
			break;
		}
	}
	std::cout << c;

	return 0;
}