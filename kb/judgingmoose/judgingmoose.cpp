/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/judgingmoose
TAGS: IO, I/O, Input, Output, Cases, Math
EXPLANATION:
If l == 0 and r == 0, print "Not a moose". Otherwise, print "Even " when l == r and "Odd " otherwise, followed by 2 * the maximum of l and r.
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned short l, r;
	std::cin >> l >> r;
	if (l == 0 && r == 0)
	{
		std::cout << "Not a moose";
	}
	else
	{
		std::cout << (l == r ? "Even " : "Odd ") << 2 * std::max(l, r);
	}

	return 0;
}