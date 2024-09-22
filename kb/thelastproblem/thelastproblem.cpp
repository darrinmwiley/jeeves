/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/thelastproblem
TAGS: String, I/O, IO, Input, Output
EXPLANATION:
Use getline to read a string from cin. Then, cout "Thank you, " followed by the string followed by ", and farewell!".
END ANNOTATION
*/

#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::string S;
	getline(std::cin, S);
	std::cout << "Thank you, " << S << ", and farewell!";

	return 0;
}