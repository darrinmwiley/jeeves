/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/rationalsequence
TAGS: number theory, tree, rational, integer, sequence
EXPLANATION:
Assuming we are not at the rightmost node in a row, to get to the next node, we must go up the tree until we are at
a left child, go to its sibling, and go back down the tree the same number of levels. Left children are of the form
p/(p+q), so their denominator is larger than their numerator; right children similarly have larger numerators than
denominators. Consider the fraction p / q; we must first go up the tree until we have reached a left node (subtract
b from a until a < b). The number of levels we will ascend is equal to d := floor(a/b), giving us (a - b * d) / b.
Then, we must go up one level from this left child (subtract the numerator from the denominator), giving us
(a - b * d) / (b + b * d - a) and go down to the right child (add the denominator to the numerator), giving us
b / (b + b * d - a). We must then descend d levels to the left (add the numerator to the denominator d times),
giving us b / (b + b * d + b * d - a). Simplified, that is b / ((floor(a / b) * 2 + 1) * b - a). In the case where
a / b is on the right edge of a row, it is of the form a / 1 and will result in 1 / (a + 1); note that plugging in
b = 1 to the previous formula actually gives us this answer. Thus, for any p / q, the next rational number will be
q / ((floor(p / q) * 2 + 1) * q - p).
END ANNOTATION
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	unsigned int P;
	cin >> P;
	for (unsigned int i = 0; i < P; i++)
	{
		unsigned int K;
		cin >> K;
		cout << K << ' ';

		string str;
		cin >> str;
		unsigned int idx = str.find('/');
		unsigned long long p = stoull(str.substr(0, idx));
		unsigned long long q = stoull(str.substr(idx + 1));

		cout << q << '/' << (p / q * 2 + 1) * q - p << '\n';
	}
	return 0;
}