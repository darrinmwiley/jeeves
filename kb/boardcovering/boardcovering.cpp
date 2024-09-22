/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/boardcovering
TAGS: DP, Dynamic Programming, Bitmask, Bitmask DP, Bitmask Dynamic Programming, Memoization, Grid, Top-Down DP, Top-Down, Top-Down Dynamic Programming, Recursion, Top Down, Top Down DP, Top Down Dynamic Programming
EXPLANATION:
Note: this explanation assumes a 12x12 grid. Simply add extra # characters to reduce the problem to this case.

To solve this problem, we can use a higher-radix variant of "rolling bitmask DP" (see https://www.youtube.com/watch?v=rlTkd4yOQpE&t=220s for a great explanation of this
technique). Essentially, we proceed by trying all possibilities for each cell and stopping when we reach an invalid state. Specifically, let our state consist of the
coordinates of the current cell (i, j), the remaining length b of the current horizontal line (positive for right, 0 for no horizontal line or a left/right boundary, and negative
for left), and, for each of the 12 columns, the remaining length M[j] of the vertical line (positive for down, 0 for no vertical line or a down/up boundary, and negative for up).
Scanning first left-to-right and top-to-bottom, we can recursively find the solution as follows:

Case 1 (j == 12): b must be 0 (a line cannot extend beyond the grid or come from the edge of the grid). Otherwise, set j to 0 and increment i, then recurse.

Case 2 (i == 12): All values of M should be 0 for the same reason b must be 0 in case 1. If this is true, we have completed a valid configuration and may return true.

Case 3 (# character): M[j] and b should be 0, as a line cannot come from/extend into a blocked cell. If this is the case, increment j and recurse.

Case 4 (. character): If b is 0, we can try a vertical line: decrement M[j], increment j, and recurse. If M[j] is 0, we can try a horizontal line: decrement b, increment j, and
					  recurse. If both b and M[j] are 0, try both options, and if neither are 0, the current configuration is automatically invalid. Also, if either decrement
					  produces a value less than -9, that option is invalid, as no digit cell can supply a line of length greater than 9.

Case 5 (digit): Let val denote the total length of the right and down lines extending from this cell. It can be computed as the cell's value plus b plus M[j]. Note that b and M[j]
				should be nonpositive (as lines cannot extend into a digit cell) and val should be nonnegative (as it must have enough capacity to source its up/left lines).
				Consider the possible combinations of right/down lines extending from the current cell. For each of the val + 1 new values of b in [0, val], setting b to that
				value, setting M[j] to val - b, and incrementing j is a possibility and should be tried.

Doing this purely recursively is inefficient, but it can be optimized by caching invalid states in a hash table (like C++'s unordered_set or Java's HashSet). This requires a
custom hash function; starting with 0 and, for each field, multiplying by 31 and adding the field is a good choice. With the above representation, the state space is huge
(12^2 * 19^13, or about 6 quintillion, possible states), so bottom-up DP will get a TLE or MLE verdict. However, almost all states are not actually reachable with the above
process, so a top-down approach (recursion + memoization) works.
END ANNOTATION
*/

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <unordered_set>

using namespace std;

constexpr array<int, 12> ZERO{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

array<array<char, 12>, 12> GIn;
array<array<char, 12>, 12> GOut;

struct State
{
	int b, i, j;
	array<int, 12> M;
	inline int& m() { return M[j]; }
	inline const int& m() const { return M[j]; }
	friend bool operator==(const State& l, const State& r)
	{
		return l.b == r.b && l.i == r.i && l.j == r.j && l.M == r.M;
	}
};

template<>
struct std::hash<State>
{
	inline size_t operator()(const State& s) const noexcept
	{
		size_t h = 0;
		for (int m : s.M)
			h = h * 31 + m;
		h = h * 31 + s.b;
		h = h * 31 + s.i;
		h = h * 31 + s.j;
		return h;
	}
};

unordered_set<State> DP;

// Returns true iff State s allows a valid configuration
bool rec(const State& s)
{
	if (s.j == 12) // Case 1
		return s.b == 0 && rec({ 0, s.i + 1, 0, s.M });
	if (s.i == 12) // Case 2
		return s.M == ZERO;

	if (DP.find(s) != DP.end()) // If memoized as an invalid state, return false.
		return false;

	char g = GIn[s.i][s.j];
	char ans = 0;

	switch (GIn[s.i][s.j])
	{
	case '#': // Case 3
		if (s.b == 0 && s.m() == 0)
		{
			State newS = s;
			newS.j++;
			if (rec(newS))
				ans = g;
		}
		break;
	case '.': // Case 4
		if (s.b == 0 && s.m() > -9) // Vertical
		{
			State newS = s;
			newS.m()--;
			newS.j++;
			if (rec(newS))
				ans = s.m() <= 0 ? '^' : 'v';
		}
		if (ans == 0 && s.m() == 0 && s.b > -9) // Horizontal
		{
			State newS = s;
			newS.b--;
			newS.j++;
			if (rec(newS))
				ans = s.b <= 0 ? '<' : '>';
		}
		break;
	default: // Case 5
		if (s.b <= 0 && s.m() <= 0)
		{
			int val = GIn[s.i][s.j] - '0';
			val += s.b + s.m();
			for (int b = 0; b <= val; b++)
			{
				State newS = s;
				newS.b = b;
				newS.m() = val - b;
				newS.j++;
				if (rec(newS))
				{
					ans = g;
					break;
				}
			}
		}
		break;
	}

	if (ans == 0) // If invalid, memoize
		DP.insert(s);
	else // Otherwise, we found a valid config; set the corresponding character in the output grid
		GOut[s.i][s.j] = ans;

	return ans != 0;
}

int main()
{
	int M, N;
	cin >> M >> N;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			if (i < M && j < N)
				cin >> GIn[i][j];
			else
				GIn[i][j] = '#'; // Pad extra # characters to make the grid 12x12.

	rec({ 0, 0, 0, ZERO });

	// The part of the grid filled with padding #'s is not printed.
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << GOut[i][j];
		cout << endl;
	}
}