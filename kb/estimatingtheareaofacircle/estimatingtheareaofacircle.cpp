/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/estimatingtheareaofacircle
TAGS: Input, Output, IO, I/O, Math
EXPLANATION:
Pi can be computed as 4 * atan(1). For the first area, print pi * r^2, and for the second, print 4 * r^2 * c / m.
Use a while loop to do this repeatedly until m is 0. Be sure to use setprecision to make your output accurate enough.
END ANNOTATION
*/

#include <iomanip>
#include <iostream>
#include <limits>
#include <math.h>

const long double PI_4 = atanl(1);

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10);

	long double r, m, c;
	std::cin >> r >> m >> c;
	do
	{
		long double r2 = 4 * r * r;
		long double A1 = r2 * PI_4;
		long double A2 = r2 * c / m;
		std::cout << A1 << ' ' << A2 << std::endl;
		std::cin >> r >> m >> c;
	}
	while (m != 0);
}