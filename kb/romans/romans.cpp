/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/romans
TAGS: IO, I/O, Input, Output, Math
EXPLANATION:
First, multiply by the given factor. Then, add 0.5 and cast to an int to round to the correct value.
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	constexpr const long double F = 880000.0l / 809.0l;

	long double X;
	std::cin >> X;
	std::cout << (unsigned int) (X * F + 0.5l);

	return 0;
}