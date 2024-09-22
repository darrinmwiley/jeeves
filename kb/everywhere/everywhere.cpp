/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/everywhere
TAGS: set, string, test case
EXPLANATION:
Run a for loop over [0, T) for the test cases. Inside, create an empty hashset of strings.
Run a for loop over [0, n) to read in each name as a string and insert it in the set. Then
output the set's size.
END ANNOTATION
*/
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main()
{
	unsigned T;
	cin >> T;
	for (unsigned t = 0; t < T; t++)
	{
		unsigned n;
		cin >> n;
		unordered_set<string> cityNames;
		for (unsigned i = 0; i < n; i++)
		{
			string cityName;
			cin >> cityName;
			cityNames.insert(cityName);
		}
		cout << cityNames.size() << endl;
	}
	return 0;
}