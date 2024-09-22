/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/timeloop
TAGS: input, output, loop
EXPLANATION:
Run a loop starting at 1 with condition i <= N. Each iteration, print i followed by " Abracadabra".
END ANNOTATION
*/

#include <iostream>

using namespace std;

int main()
{
	unsigned N;
	cin >> N;
	for (unsigned i = 1; i <= N; i++)
		cout << i << " Abracadabra" << endl;
}