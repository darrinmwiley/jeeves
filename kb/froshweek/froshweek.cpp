/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/froshweek
TAGS: BIT
EXPLANATION:
While the array is not sorted, there will always be an adjacent pair that is out of order and can be swapped.
Look at the number of pairs of integers in the array such that the one that comes first is greater than the second.
Swapping out of order adjacent pairs reduces this number by 1, and a sorted array has none of these pairs.
Therefore, the answer is the number of pairs of out of order integers.

We iterate through the array, updating a BIT, and check how many of the integers encountered so far are out of order,
compared to the current integer.
The sum will give the answer.

Implementation note: Since the values are from 1-1000000000, a BIT of this size is too large, so we can instead sort the array,
preserving the original indices, and run the algorithm on these indices.
END ANNOTATION
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

int N;
vector<int> arr;
vector<pii> pts;
vector<int> BIT;

void add(int ind) {
	while (ind <= N) {
		BIT[ind]++;
		ind += ind & (-ind);
	}
}

int getSum(int ind) {
	int sum = 0;
	while (ind > 0) {
		sum += BIT[ind];
		ind -= ind & (-ind);
	}
	return sum;
}

int main()
{
	cin >> N;
	arr = vector<int>(N);
	pts = vector<pii>(N);
	BIT = vector<int>(N + 1);
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		arr[i] = x;
		pts[i] = make_pair(x, i);
	}

	long long ans = 0;
	sort(pts.begin(), pts.end());
	for (int i = N - 1; i >= 0; i--) {
		ans += getSum(pts[i].second + 1);
		add(pts[i].second + 1);
	}

	cout << ans << endl;

	return 0;
}