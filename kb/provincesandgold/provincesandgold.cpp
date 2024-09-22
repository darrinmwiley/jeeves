/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/provincesandgold
TAGS: IO, I/O, Input, Output, Cases, Math
EXPLANATION:
The buying power can be calculated as P = G * 3 + S * 2 + C * 1. First, output "Province or " if P>=8, else "Duchy or " if P>=5,
else "Estate or " if P>=2. Then, output "Gold" if P>=6, else "Silver" if P>=3, else "Copper".
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned short G, S, C, P;
	std::cin >> G >> S >> C;
	P = G * 3 + S * 2 + C * 1;

	if (P >= 8)
	{
		std::cout << "Province or ";
	}
	else if (P >= 5)
	{
		std::cout << "Duchy or ";
	}
	else if (P >= 2)
	{
		std::cout << "Estate or ";
	}

	if (P >= 6)
	{
		std::cout << "Gold";
	}
	else if (P >= 3)
	{
		std::cout << "Silver";
	}
	else
	{
		std::cout << "Copper";
	}

	return 0;
}