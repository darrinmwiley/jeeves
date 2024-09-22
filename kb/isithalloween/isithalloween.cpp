/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/isithalloween
TAGS: IO, I/O, Input, Output, Cases
EXPLANATION:
Input the line to a string. If the string equals "OCT 31" or "DEC 25", print "yup", else print "nope".
END ANNOTATION
*/

#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::string str;
	getline(std::cin, str);
	std::cout << (str == "OCT 31" || str == "DEC 25" ? "yup" : "nope");

	return 0;
}