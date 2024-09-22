/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/tarifa
TAGS: IO, I/O, Input, Output, Math
EXPLANATION:
The answer can be found by subtracting each P_i from X * (N + 1).
END ANNOTATION
*/

#include<iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned X, N, V;
	std::cin >> X >> N;

	V = X * (N + 1);
	for(unsigned i = 0; i < N; i++)
	{
		unsigned P;
		std::cin >> P;
		V -= P;
	}
	std::cout << V;

	return 0;
}