/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/r2
TAGS: input, output, math
EXPLANATION:
Calculate r2 = 2 * s - r1.
END ANNOTATION
*/
#include <iostream>

using namespace std;

int main()
{
	int r1, r2, s;
	cin >> r1 >> s;
	r2 = 2 * s - r1;
	cout << r2;
}