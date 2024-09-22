/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/onechicken
TAGS: IO, I/O, Input, Output, String, Formatting
EXPLANATION:
If N < M, output the first message (with P); otherwise output the second message. Be sure to use a ternary to print nothing ("")
if P or Q are 1 and "s" otherwise so piece(s) is plural iff there are multiple pieces of chicken in question.
END ANNOTATION
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned short N, M;
	std::cin >> N >> M;
	if (N < M)
	{
		unsigned short P = M - N;
		std::cout << "Dr. Chaz will have " << P << " piece" << (P == 1 ? "" : "s") << " of chicken left over!";
	}
	else
	{
		unsigned short Q = N - M;
		std::cout << "Dr. Chaz needs " << Q << " more piece" << (Q == 1 ? "" : "s") << " of chicken!";
	}

	return 0;
}