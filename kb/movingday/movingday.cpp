/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/movingday
TAGS: volume, geometry, maximum, long
EXPLANATION:
Loops through each box, computing its volume and updating the maximum volume. At the end, prints the maximum
box volume minus V. Volumes are represented as long longs because they could be up to 2^32 (which would allow
the use of an unsigned int), but they are also signed (i.e. the result of the subtraction).
END ANNOTATION
*/
#include <iostream>

using namespace std;

int main()
{
	// Reads n and V.
	unsigned n;
	cin >> n;
	long long V;
	cin >> V;

	// Stores the maximum box volume
	long long maxV = 0;

	// Loops through each box
	for (unsigned i = 0; i < n; i++)
	{
		// Reads in length, width, and height
		long long l, w, h;
		cin >> l >> w >> h;

		// Computes this box's volume
		long long v = l * w * h;

		// Updates the maximum volume
		if (v > maxV)
			maxV = v;
	}

	// Prints d_i for the box with volume maxV.
	cout << maxV - V;

	return 0;
}