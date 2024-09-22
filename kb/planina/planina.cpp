/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/planina
TAGS: input, output, math
EXPLANATION:
The result is equal to (2^N + 1)^2. 2^N can be calculated as 1<<N.
END ANNOTATION
*/
#include <iostream>

using namespace std;

int main()
{
	unsigned N;
	cin >> N;

	unsigned res = (1u << N) + 1;
	cout << res * res;

	return 0;
}