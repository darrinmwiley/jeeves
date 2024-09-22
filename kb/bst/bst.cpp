/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/bst
TAGS: binary search tree, binary tree, tree, depth, interval, successor
EXPLANATION:
A node in a binary search tree can be thought of as a pair of intervals representing all values that are present in or could be inserted
into its left and right subtrees. When a new node is inserted, its intervals become the appropriate parent interval split to the left
and to the right of the new node's value. An example of these intervals for sample input 2 is given below:

Initial:
_____
12345

3 Inserted:
__ __
_____
12345

2 Inserted:
_
__ __
_____
12345

4 Inserted:
_   _
__ __
_____
12345

1 Inserted:
_   _
__ __
_____
12345

5 Inserted:
_   _
__ __
_____
12345

As you can see, the depth of a node is equal to the number of intervals it is in. Thus, by keeping track of the depth of the deepest
intervals, the depth of a new node can be computed. This can be done by maintaining an ordered map of these intervals, where the key
is the rightmost position where they are the deepest interval and the value is the depth. Trivially, this map is initialized
to map N + 1 to 0. For each insertion, first find the deepest interval the new node is part of. This can be done quickly by finding its
successor in the map. Then, increment the depth of that interval (which now corresponds to the right subtree). Add an interval ending at
the inserted value with the new depth (representing the left subtree). The original interval does not need to be re-inserted,
as no node can be inserted where a node already exists and so that interval will never be used again. Repeat this for each insertion.
The time complexity is clearly logarithmic in N per iteration.
END ANNOTATION
*/

#include <iostream>
#include <map>

using namespace std;

int main()
{
	int N;
	cin >> N;
	map<int, int> S;
	S.emplace(N + 1, 0);
	long long C = 0;
	for (int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		map<int, int>::iterator lIter = S.upper_bound(x);
		int last = lIter->first, depth = lIter->second;
		C += depth;
		S.emplace(x, depth + 1);
		lIter->second = depth + 1;
		cout << C << endl;
	}
}