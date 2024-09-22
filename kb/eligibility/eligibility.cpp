/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/eligibility
TAGS: IO, I/O, Input, Output, String, Cases
EXPLANATION:
You can use std::setw to read exactly 4 characters to parse the year and exactly 6 characters to a dummy variable
to skip the month and day. If the post-secondary studies year is >= 2010 or the year of birth is >= 1991, print
the eligible message; otherwise, if the number of courses is >= 2010, print the ineligible message; otherwise,
print the coach petition message.
END ANNOTATION
*/

#include <iomanip>
#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	unsigned int tCases;
	std::cin >> tCases;
	for (unsigned int tCase = 0; tCase < tCases; tCase++)
	{
		std::string name;
		unsigned int pssYear, dobYear, courses;
		std::string dummy;

		std::cin >> name >> std::setw(4) >> pssYear >> std::setw(6) >> dummy >> std::setw(4) >> dobYear >> std::setw(6) >> dummy >> courses;
		std::cout << name;

		if (pssYear >= 2010 || dobYear >= 1991)
		{
			std::cout << " eligible";
		}
		else if (courses >= 41)
		{
			std::cout << " ineligible";
		}
		else
		{
			std::cout << " coach petitions";
		}

		std::cout << std::endl;
	}

	return 0;
}