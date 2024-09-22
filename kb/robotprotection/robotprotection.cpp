/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/robotprotection
TAGS: convex hull, shoelace theorem
EXPLANATION:
Find convex hull of set of points with Graham Scan
Use shoelace theorem to find area of the convex hull
END ANNOTATION
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

struct point {
	int x,y;
};

long double area(vector<point> points) {
	long double area = 0.0;
	size_t n =points.size();
	for(size_t i = 0; i < n; i++){
		area += points[i].x * points[(i+1)%n].y;
		area -= points[i].y * points[(i+1)%n].x;
	}
	return fabs(area)/2.0;
}

enum orientation{CW, CCW, CL};
orientation getOrientation(point a, point b, point c) {
	int o = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
	if ( o == 0 ) return CL;
	return (o < 0)?CW:CCW;
}

void convex_hull(vector<point>& a, point p0) {
	sort(a.begin(), a.end(), [&p0](const point& a, const point& b) {
			orientation o = getOrientation(p0,a,b);
			if (o == CL) {
				return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y) 
				< (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
			}
			return o == CW;
			});
	vector<point> S;
	for (size_t i = 0; i < a.size(); i++) {
		while (S.size() > 1 && getOrientation(S[S.size()-2], S.back(), a[i]))
			S.pop_back();
		S.push_back(a[i]);
	}

	a = S;
}

int main() {
	while (!cin.eof()){
		int n; cin >> n;
		if ( n == 0 ) break;
		vector<point> L;
		point minp;
		minp.x = 10001;
		minp.y = 10001;
		while(n--) {
			point p;
			cin >> p.x >> p.y;
			if ( p.y < minp.y )
				minp = p;
			else if ( p.y == minp.y )
				if (p.x < minp.x)
					minp = p;
			L.push_back (p);
		}
		convex_hull(L, minp);
		cout << fixed << setprecision(1) << area(L) << '\n';
	}

	return 0;
}
