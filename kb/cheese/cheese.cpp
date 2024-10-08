/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cheese
TAGS: binary search, geometry, volume, math, sphere
EXPLANATION:
This explanation uses millimeters for all units. Some input is in micrometers, so it must first be converted.
In order to solve this problem, we first must be able to compute the volume of the slice from 0 to sz for some value sz.
This can be done by first finding the volume without holes (10,000*sz). Then, subtract the volume of holes fully included in the
slice (4/3*pi*r^3). Finally, subtract the volume of the intersection of holes partially in the slice with the slice. Define h as the
height of the clipped sphere formed from this intersection. It can be computed as sz - (z - r). The volume of this clipped sphere
can be found by integrating the area of the circular cross section from -r to h-r. At position a in [-r, h-r], the radius of this
cross section is sqrt(r^2-a^2) by the Pythagorean Theorem, and so its area is pi(r^2-a^2). Integrating this, we get a volume of
pi*h^2(r-h/3).
First, compute the volume V of the entire block of cheese (by setting sz to 100). Then, we must compute the values of sz that make the
volume V/s, 2V/s, ..., all the way up to V. (Then, computing the width of a slice simply corresponds to subtracting adjacent values of
sz). Luckily, the volume increases monotonously (as including more of the block of cheese cannot decrease the total volume), so we can
compute these values of sz by binary search. For each iteration, set the lower bound to 0 and the upper bound to 100. Then, if the
volume computed in the middle of these two bounds is too small, set the lower bound to the middle, and otherwise, set the upper bound
to the middle. Repeat this until the bounds are within a safe threshold (like 10^-7); the correct sz value is then their average.
Finally, print the differences between adjacent sz values.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

const double PI = atanl(1) * 4;
const double PI43 = PI * 4 / 3;

struct Hole
{
	double r, x, y, z, v, minZ, maxZ;
	double volume(double sz) const // volume of the intersection of this hole with the slice from 0 to sz
	{
		if (maxZ <= sz) // Fully included
			return v;
		else if (minZ < sz) // Partially included
		{
			double h = sz - minZ;
			return PI * h * h * (r - h / 3);
		}
		else // Excluded
			return 0;
	}
	friend istream& operator>>(istream& strm, Hole& h)
	{
		strm >> h.r >> h.x >> h.y >> h.z;
		h.r *= 0.001;
		h.x *= 0.001;
		h.y *= 0.001;
		h.z *= 0.001;
		h.v = PI43 * h.r * h.r * h.r;
		h.minZ = h.z - h.r;
		h.maxZ = h.z + h.r;
		return strm;
	}
	// Compare by maximum z coordinate
	friend bool operator<(const Hole& l, const Hole& r)
	{
		return l.maxZ < r.maxZ;
	}
};

int n, s;
vector<Hole> H;

double volume(double sz)
{
	double ans = 10'000 * sz;
	for (const Hole& h : H)
		ans -= h.volume(sz);
	return ans;
}

int main()
{
	cin >> n >> s;
	H.resize(n);
	for (int i = 0; i < n; i++)
		cin >> H[i];
	double V = volume(100);
	double prev = 0;
	for (int i = 1; i <= s; i++)
	{
		double target = V * i / s;
		double lo = 0, hi = 100, mid = 50;
		while (hi - lo > 1.0e-7)
		{
			double v = volume(mid);
			if (v < target)
				lo = mid;
			else
				hi = mid;
			mid = (hi + lo) / 2;
		}
		cout << fixed << setprecision(7) << mid - prev << endl;
		prev = mid;
	}
}