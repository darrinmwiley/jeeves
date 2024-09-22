/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/temperature
TAGS: IO, I/O, Input, Output, Math, Cases
EXPLANATION:
If Y==1, then if X==0, print ALL GOOD, else print IMPOSSIBLE. Otherwise, print X / (1 - Y). Don't forget to cast to a floating point
before doing the division to prevent rounding down, and set a high enough precision with std::setprecision to reach the required accuracy.
END ANNOTATION
*/

#include <iomanip>
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	short X, Y;
	std::cin >> X >> Y;

	if (Y == 1)
	{
		if (X == 0)
		{
			std::cout << "ALL GOOD";
		}
		else
		{
			std::cout << "IMPOSSIBLE";
		}
	}
	else
	{
		std::cout << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10) << X / (1.0l - Y);
	}

	return 0;
}