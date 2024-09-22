/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/different
TAGS: IO, I/O, Input, Output, Math, Difference
EXPLANATION:
Use 64-bit ints to contain the large input. Use while (cin >> a >> b) as a loop to accept input while it exists.
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned long long a, b;
	while (std::cin >> a >> b)
	{
		std::cout << (a > b ? a - b : b - a) << std::endl;
	}

	return 0;
}