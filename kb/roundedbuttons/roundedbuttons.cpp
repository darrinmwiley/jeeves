/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/roundedbuttons
TAGS: geometry, math
EXPLANATION:
First, note that the rounded rectangle can be broken into regions, as shown below:

   /+-----+\       +-----+
  / |     | \      |     |
 /  |     |  \     |     |
/   |     |   \    |     |
+---+-----+---+    |     |   +-------------+      /+   +\      +---+   +---+
|   |     |   |    |     |   |             |     / |   | \     \ E |   | F /
|   |     |   | == |  A  | U |      B      | U  /  | U |  \  U  \  | U |  /
|   |     |   |    |     |   |             |   / C |   | D \     \ |   | /
+---+-----+---+    |     |   +-------------+   +---+   +---+      \+   +/
\   |     |   /    |     |
 \  |     |  /     |     |
  \ |     | /      |     |
   \+-----+/       +-----+

(The weird triangular shapes are supposed to be quarter circles. However, I am bad at drawing circles, especially with ASCII art.)

Thus, to test if a point is inside the rounded rectange, simply test whether the point is inside at least one of those regions.
Rectangle A consists of x coordinates from x + r to x + w - r and y coordinates from y to y + h. Rectangle B consists of x coordinates
from x to x + w and y coordinates from y + r to y + h - r. To check whether a point (X, Y) is inside a rectangle with x ranging from
x1 to x2 and y ranging from y1 to y2, check that x1 <= X, X <= x2, y1 <= Y, and Y <= y2. If the given point is inside either of these
rectangles, the answer is inside. Otherwise, we must check if the point is inside the corner quarter-circles. C is part of a circle
centered at (x + r, y + r), D is part of a circle centered at (x + w - r, y + w), E is part of a circle centered at (x + r, y + h - r),
and F is part of a circle centered at (x + w - r, y + h - r). All of these circles have radius r. To check whether a point (X, Y) is
inside a circle centered at (x1, y1) with radius r, simply compute the distance sqrt((X - x1)^2 + (Y - y1)^2) between (X, Y) and
(x1, y1); if the distance is > r, the point is outside; otherwise, it is inside. This can be made slightly simpler by squaring both
sides of the inequality: (X, Y) is outside (x1, y1) if and only if (X - x1)^2 + (Y - y1)^2 > r^2. If a point was outside the rectangles
then the answer is inside if and only if it is inside at least one of these circles. Note that we can treat the quarter-circles as full
circles because the remaining part of each circle is still inside the rounded rectangle and thus does not change the answer.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>

using namespace std;

double dist2(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1, dy = y2 - y1;
	return dx * dx + dy * dy;
}

bool insideRectangle(double X, double Y, double x1, double y1, double x2, double y2)
{
	return x1 <= X && X <= x2 && y1 <= Y && Y <= y2;
}

bool insideCircle(double X, double Y, double x1, double y1, double r)
{
	double dx = X - x1, dy = Y - y1;
	return dx * dx + dy * dy <= r * r;
}

int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		double x, y, w, h, r;
		cin >> x >> y >> w >> h >> r;

		int m;
		cin >> m;
		while (m--)
		{
			double X, Y;
			cin >> X >> Y;

			bool inside =
				insideRectangle(X, Y, x + r, y, x + w - r, y + h) || // A
				insideRectangle(X, Y, x, y + r, x + w, y + h - r) || // B
				insideCircle(X, Y, x + r, y + r, r) || // C
				insideCircle(X, Y, x + w - r, y + r, r) || // D
				insideCircle(X, Y, x + r, y + h - r, r) || // E
				insideCircle(X, Y, x + w - r, y + h - r, r); // F
			cout << (inside ? "inside" : "outside") << endl;
		}
		cout << endl;
	}
}