/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/moscowdream
TAGS: IO, Input, Output, I/O, Math
EXPLANATION:
If a, b, and c are all >= 1 and n >= 3 (so at least one problem of each difficulty may be chosen), and a + b + c >= n (so n problems may be chosen), print YES, else NO.
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned short a, b, c, n;
	std::cin >> a >> b >> c >> n;
	std::cout << (a >= 1 && b >= 1 && c >= 1 && a + b + c >= n && n >= 3 ? "YES" : "NO");

	return 0;
}