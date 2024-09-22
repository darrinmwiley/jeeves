/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/leylines
TAGS: sweep, radial sweep, trig, trigonometry, geometry, math
EXPLANATION:
For a given pivot point, consider an infinitely long strip of thickness t, where the pivot is on one edge of the strip. Let us sweep the strip radially,
starting horizontally with the pivot at the bottom. If we can figure out how many points are initially in this strip and when points are added and removed
as the strip sweeps, we can figure out the maximum number of points in a strip including the pivot and one other point on the border. Since an optimal
solution can always be constructed with two points on the border, iterating this for all pivots gives the correct result. The complexity per pivot is
O(n * log(n)) for sorting the list of events, so the overall complexity is O(n^2 * log(n)), which is fine for n=3000 with a time limit of 13 seconds.

First, consider the times the bottom line (the one passing through the pivot) intersects a point. The ray that starts in the +x direction from the pivot
does this at angle atan2(dy, dx), where <dy, dx> is the vector from the pivot to the current point. The ray that starts in the -x direction intersects at
this angle plus pi. We are sweeping counterclockwise, so the point is removed when the +x ray touches it and is added when the -x ray touches it. Be careful
that angles remain in [0, 2pi).

Next, if the distance between the pivot and the point is more than t, the point will touch the top of the strip twice. Consider a right triangle with corners
at the pivot, the current point, and the closest point to the current point on the other side of the strip. The side opposite the pivot has length t (as it
connects two points on opposite sides of the strip) and the hypotenuse has length equal to the disance between the point and the pivot. Thus, the angle at the
pivot (called phi) is the arcsin of t over that distance. In the initially +x direction, the current sweep angle plus phi points at the current point, so the
sweep angle is atan2(dy, dx) - phi. In the -x direction, the sweep angle minus phi points away from the current point, so the sweep angle is
atan2(dy, dx) + pi + phi. The +x direction adds the point and the -x direction removes it. Remember to keep angles in [0, 2pi) and avoid points with distance at
most t from the pivot.

To count the points that start inside the strip, first include the pivot. Then, if the angle to the point is less than pi and dy is at most t, count the point.
After this, iterate over the events described in the above two paragraphs in order of nondecreasing angle. Keep track of the maximum number of points achieved.
After doing this for all pivots, we have the optimal answer.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct Event
{
	long double a;
	bool ex;

	inline Event(long double a, bool ex) :
		a(a),
		ex(ex)
	{}

	bool operator<(const Event& e)
	{
		if (a != e.a)
			return a < e.a;
		return ex < e.ex;
	}
};

const long double PI = atanl(1) * 4;

int main()
{
	int n;
	long double t;
	cin >> n >> t;

	if (t == 0)
	{
		cout << 2;
		return 0;
	}

	vector<long double> X(n), Y(n);
	for (int i = 0; i < n; i++)
		cin >> X[i] >> Y[i];

	vector<Event> E;

	int maxC = 0;
	for (int i = 0; i < n; i++)
	{
		E.clear();
		long double x1 = X[i], y1 = Y[i];
		int c = 1; // start at 1 to include the pivot
		for (int j = 0; j < n; j++)
		{
			if (j == i) continue;
			long double dx = X[j] - X[i], dy = Y[j] - Y[i];
			long double a1 = atan2l(dy, dx);
			if (a1 < 0) a1 += 2 * PI;
			if (a1 < PI && dy < t)
				c++;
			long double a2 = a1 + PI;
			if (a2 >= 2 * PI)
				a2 -= 2 * PI;
			E.emplace_back(a1, true);
			E.emplace_back(a2, false);

			long double r2 = dx * dx + dy * dy;
			if (r2 <= t * t) continue;

			long double phi = asinl(t / sqrtl(r2));
			long double a3 = a1 - phi;
			if (a3 < 0) a3 += 2 * PI;
			long double a4 = a2 + phi;
			if (a4 >= 2 * PI) a4 -= 2 * PI;
			E.emplace_back(a3, false);
			E.emplace_back(a4, true);
		}

		sort(E.begin(), E.end());

		if (c > maxC)
			maxC = c;
		for (Event e : E)
		{
			if (e.ex)
				c--;
			else
				maxC = max(maxC, ++c);
		}

	}

	cout << maxC;
}