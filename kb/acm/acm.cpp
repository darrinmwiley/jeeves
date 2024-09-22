/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/acm
TAGS: string, array, math, input, output, IO, I/O
EXPLANATION:
Store an array of 26 penalties, a primary measure, and a secondary measure, all initialized to 0. While the end of the standard input has not been reached, read m, the problem letter,
and a string. Subtract 'A' from the letter so it can be used as an array index. if the string is "right", increment the primary measure (since another problem was solved) and increase the
secondary measure by m plus 20 times the value in penalties at index p. This is because this problem did not count towards the secondary measure before, but it now does. Otherwise, the
submission will be wrong, so just increment the penalties array at index p. Once EOF has been reached, print the primary and secondary measures separated by a space.
END ANNOTATION
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int m;
	char p;
	string str;
	int primary = 0, secondary = 0;
	int penalties[26]{};
	while (cin >> m >> p >> str)
	{
		p -= 'A';
		if (str == "right")
		{
			primary++;
			secondary += m + 20 * penalties[p];
		}
		else
			penalties[p]++;
	}

	cout << primary << ' ' << secondary;

	return 0;
}
