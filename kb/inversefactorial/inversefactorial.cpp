/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/inversefactorial
TAGS: number theory, approximation, binary search, factorial, logarithm, digits, string
EXPLANATION:
Binary search over the number of digits. For a given n, use the logarithm of Stirling's Approximation
to compute the number of digits in n!. Hardcode all values of n < 7, as the number of digits there will
be repeated.
END ANNOTATION
*/

#include <iostream>
#include <math.h>
#include <string>

using namespace std;

const long double logE = 1 / logl(10);
const long double a = log10l(2 * sqrtl(2 * atanl(1)));

// approximates floor(log10(n!)) + 1.
unsigned int stirlingDigits(unsigned int n)
{
	return static_cast<unsigned int>(a - logE * n + (n + 0.5) * log10l(n)) + 1;
}

int main()
{
	string str;
	cin >> str;
	const unsigned int x = str.size();
	if (x <= 3)
	{
		switch (x)
		{
		case 1:
			switch (str[0])
			{
			case '1':
				cout << '1';
				break;
			case '2':
				cout << '2';
				break;
			default:
				cout << '3';
				break;
			}
			break;
		case 2:
			cout << '4';
			break;
		default:
			switch (str[0])
			{
			case '1':
				cout << '5';
				break;
			default:
				cout << '6';
				break;
			}
			break;
		}
		return 0;
	}
	unsigned int min = 7, max = 205022, mid;
	while (max >= min)
	{
		mid = (min + max) / 2;
		unsigned int y = stirlingDigits(mid);
		if (y == x)
		{
			cout << mid;
			return 0;
		}
		else if (y < x)
		{
			min = mid + 1;
		}
		else
		{
			max = mid - 1;
		}
	}

	// should never occur
	throw 0;
}