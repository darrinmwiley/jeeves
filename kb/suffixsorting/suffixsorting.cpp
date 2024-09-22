/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/suffixsorting
TAGS: suffix, array, suffix array, string, strings
EXPLANATION:
This problem can be solved easily by constructing a suffix array. While linear time construction is possible, for this problem,
a simple O(|s|lg^2(|s|)) solution suffices. First, sort each (nonempty) suffix by its first two characters. This can be done by
assigning to each suffix a pair consisting of its first character and its next character (or -1 if the suffix is one character long)
and then sorting the pairs lexicographically. If the list is already sorted by the first k characters, it can be sorted by the first
2*k characters similarly. The first element of the pair is set to the index of the pair in the sorted list, unless the pair is equal to
the previous pair, in which case it is set to the previous pair's first index. The second element of each pair is simply the first
element of the pair corresponding to the suffix starting k characters later (or -1 if there is no such suffix). Thus, sorting these pairs
lexicographically corresponds to sorting first by the first k characters and then by the next k characters. Repeating this process until
the suffixes have been sorted by all of their characters requires O(|s|lg(|s|)) time for bookkeeping work and requires O(lg(|s|)) calls
to sort (which take O(|s|lg(|s|)) time each), giving a total time complexity of O(|s|lg^2(|s|)). Furthermore, if each tuple additionally
stores the index of the first character of the suffix it represents, this results in the values of the suffix array in order. Each query q
can simply print the qth such index.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Suffix
{
	// Index of the first character of this suffix
	int idx;
	std::pair<int, int> ranks;
	inline Suffix(int idx, int curRank) :
		idx(idx),
		ranks{ curRank, -1 }
	{}
	friend bool operator<(const Suffix& l, const Suffix& r)
	{
		return l.ranks < r.ranks;
	}
};

std::vector<int> suffixArray(const std::string& s)
{
	std::vector<Suffix> suffixes;
	std::vector<int> nextRank(s.size());
	suffixes.reserve(s.size());
	// Suffixes' ranks based on their first character simply correspond to the value of that character.
	for (int i = 0; i < s.size(); i++)
		suffixes.emplace_back(i, s[i]);

	// Stores the position of each suffix in the array
	std::vector<int> indices(s.size());

	for (int n = 1; n <= 2 * s.size(); n *= 2)
	{
		for (int i = 0; i < s.size(); i++)
			indices[suffixes[i].idx] = i;

		for (int i = n; i < s.size(); i++)
		{
			suffixes[indices[i - n]].ranks.second = suffixes[indices[i]].ranks.first;
		}
		std::sort(suffixes.begin(), suffixes.end());

		// Compute new ranks for suffixes based on their position in the sorted array and their previous ranks.

		nextRank[0] = 0;
		for (int i = 1; i < s.size(); i++)
		{
			// Current and previous suffixes are equal thus far.
			if (suffixes[i].ranks == suffixes[i - 1].ranks)
				nextRank[i] = nextRank[i - 1];
			// Current suffix comes after the previous suffix.
			else
				nextRank[i] = nextRank[i - 1] + 1;
		}
		for (int i = 0; i < s.size(); i++)
			suffixes[i].ranks = { nextRank[i], -1 };
	}

	std::vector<int> ans;
	ans.reserve(s.size());
	for (const Suffix& suffix : suffixes)
		ans.push_back(suffix.idx);
	return ans;
}

int main()
{
	std::string s, dummy;
	int n;
	while (std::getline(std::cin, s) >> n)
	{
		std::vector<int> sa = suffixArray(s);

		for (int i = 0; i < n; i++)
		{
			int q;
			std::cin >> q;
			std::cout << sa[q] << ' ';
		}

		// Skips newline at the end of the list of queries.
		std::getline(std::cin, dummy);
		std::cout << std::endl;
	}
}