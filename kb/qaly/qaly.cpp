/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/qaly
TAGS: math, sum, input, output
EXPLANATION:
Make a floating point variable called sum set to zero. Loop over [0, N), adding Q * y to sum each time. Print sum.
END ANNOTATION
*/
#include <iostream>
#include <limits>

using namespace std;

int main()
{
	cout.precision(numeric_limits<long double>::max_digits10);
	
	unsigned N;
	cin >> N;

	long double sum = 0;
	for (unsigned i = 0; i < N; i++)
	{
		long double q, y;
		cin >> q >> y;
		sum += q * y;
	}

	cout << sum;
	return 0;
}