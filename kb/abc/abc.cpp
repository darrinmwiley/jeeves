/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/abc
TAGS: sort, array
EXPLANATION:
First, create an array of 3 ints. Read the 0th, 1st, and 2nd elements of that array from standard input. Then, sort the list. Finally, read in 3 characters. For each
character, subtract 'A' to get the index in the array, and print that number followed by a space..
END ANNOTATION
*/

#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	int abc[3];
	cin >> abc[0] >> abc[1] >> abc[2];
	sort(abc, abc + 3);
	char ch;
	while (cin >> ch)
		cout << abc[ch - 'A'] << ' ';
}
