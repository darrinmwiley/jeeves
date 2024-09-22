/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/oddities
TAGS: IO, I/O, Input, Output, Loop, Math
EXPLANATION:
In a loop over [0, n), read in x and print x. Then print " is odd" if x%2!=0 and " is even" otherwise.
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned short n;
	std::cin >> n;
	for (unsigned short i = 0; i < n; i++)
	{
		short x;
		std::cin >> x;
		std::cout << x << ((x & 1) ? " is odd" : " is even") << std::endl;
	}

	return 0;
}