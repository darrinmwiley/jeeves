/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/twostones
TAGS: io, input, output, even, odd, game
EXPLANATION:
Alice wins whenever N is odd; Bob wins whenever N is even.
END ANNOTATION
*/
#include <iostream>

using namespace std;

int main()
{
	unsigned N;
	cin >> N;
	if (N % 2 == 0)
		cout << "Bob";
	else
		cout << "Alice";
	return 0;
}