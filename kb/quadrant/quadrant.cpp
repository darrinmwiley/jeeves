/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/quadrant
TAGS: IO, I/O, Input, Output, Cases
EXPLANATION:
Simply use nested if-else statements. If y>0, then if x>0, print 1, else print 2. Otherwise, if x<0, print 3, else print 4.
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	short x, y;
	std::cin >> x >> y;
	if (y > 0)
	{
		if (x > 0)
		{
			std::cout << '1';
		}
		else
		{
			std::cout << '2';
		}
	}
	else
	{
		if (x < 0)
		{
			std::cout << '3';
		}
		else
		{
			std::cout << '4';
		}
	}

	return 0;
}