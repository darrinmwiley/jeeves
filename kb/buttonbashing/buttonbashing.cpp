/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/buttonbashing
TAGS: dynamic programming, dp
EXPLANATION:
Stores the minimum number of presses required to get to each time. Every time is unreachable
by default (except 0, which takes 0 presses). For each p, times reachable from those which
took p presses to reach, and which have not already been reached, are reachable in p+1 times.
This stops when no new times are reached in one iteration.
END ANNOTATION
*/
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	unsigned testCaseCount;
	cin >> testCaseCount;
	for (unsigned testCaseIndex = 0; testCaseIndex < testCaseCount; testCaseIndex++)
	{
		// Reads test case data
		unsigned n, t;
		cin >> n >> t;
		vector<int> b;
		for (unsigned i = 0; i < n; i++)
		{
			unsigned bi;
			cin >> bi;
			// Skips buttons that add no time because they are irrelevant
			if (bi != 0)
				b.push_back(bi);
		}
		
		// Checks for a desired time of 0.
		if (t == 0)
		{
			cout << "0 0" << endl;
			continue;
		}

		n = b.size();

		// Sets up dp, which stores the minimum button presses required to get to each time 
		vector<int> dp(3601, -1);
		dp[0] = 0;

		// Generates dp's contents, stopping when no new times are reachable
		bool stop;
		unsigned presses = 0;
		do
		{
			stop = true;
			presses++;
			for (int bi : b)
			{
				for (unsigned j = 0; j <= 3600; j++)
				{
					if (dp[j] == presses - 1)
					{
						unsigned k = max(0, min(3600, (int)j + bi));
						if (dp[k] == -1)
						{
							dp[k] = presses;
							stop = false;
						}
					}
				}
			}
		}
		while (!stop);

		// Prints the number of presses and the extra seconds
		for (unsigned i = t; i <= 3600; i++)
		{
			if (dp[i] >= 0)
			{
				cout << dp[i] << " " << i - t << endl;
				break;
			}
		}
	}
	return 0;
}