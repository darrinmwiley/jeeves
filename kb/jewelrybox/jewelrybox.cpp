/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/jewelrybox
TAGS: math, calculus, binary search, ternary search, algebra
EXPLANATION:
The optimal box always stretches to the edge of the paperboard, so a = X - 2 * h and b = Y - 2 * h, which gives V=h(X-2h)(Y-2h).
Therefore, we simply need to find the maximum value of this function for h in [0, min(X, Y)/2]. Looking at V's equation, we can see
that it has roots at h = 0, X/2, and Y/2. Also, the function is nonnegative over [0, min(X, Y)/2], since the volume of the box cannot
be negative. Therefore, the function's graph is unimodal and downward-opening over [0, min(X, Y)/2]. The problem then reduces to finding
the absolute maximum of this region. Some ways to do this are as follows:

Calculus:
V is a cubic polynomial in h and can be written as 4h^3-2(X+Y)h^2+XYh. Its derivative is 12h^2-4(X+Y)h+XY, which is quadratic, so its
roots can be found using the quadratic formula. they are (4(X+Y) +/- sqrt((4(X+Y))^2-4*12XY))/(2*12), which simplifies to
(X+Y +/- sqrt(X^2-XY+Y^2))/6. Note that the result corresponding to the - case is inside [0, min(X, Y)/2] and is a local maximum (since
the function increases at h=0) and the + case is a local minimum. Thus, we only need to care about the - case. Furthermore, the interval
[0, min(X, Y)/2] is unimodal, so we can ignore the endpoints. The answer is just the volume computed at h=(X+Y-sqrt(X^2-XY+Y^2))/6. This
solution runs in O(1) time.

Binary Search:
Instead of solving for where the derivative is 0, we can simply binary search for it. V's derivative is 12h^2-4(X+Y)h+XY (see the
direct computation approach for details). V's second derivative is then 24h-4(X+Y). V's inflection point, where this equals 0, satisfies
24h-4(X+Y)=0, or equivalently, h=4(X+Y)/24 = (X+Y)/6. Therefore, when h is in [0, (X+Y)/6], V' decreases monotonously. At the solution,
V'' is negative, so it must occur before this inflection point and thus must be in the range [0, (X+Y)/6]. This means that the problem
can be solved by binary searching [0, (X+Y)/6] for where V' is 0, where V' is either computed as (V(h+epsilon) - V(h))/epsilon, where
epsilon is a small, positive number, or as 12h^2-4(X+Y)h+XY. Iterate binary search until the current range's size is less than some
threshold depending on the required precision (10^-7 is safe). This solution runs in O(lg((X+Y)/precision)) time.

Ternary Search:
Instead of using the derivative, you can simply run ternary search on the range [0, min(X, Y)/2], since it is unimodal. To perform an
iteration of ternary search on the range [a, b], compute the value of V at h=(2a+b)/3 and at h=(a+2b)/3. If the first value is larger,
values of h less than (2a+b)/3 can be ruled out, and if the second value is larger, values of h greater than (a+2b)/3 can be ruled out.
Like with binary search, repeat this process until the size of the range reaches a safe threshold (such as 10^-7). This solution runs
in O(lg((X+Y)/precision)) time.

Quaternary Search:
For the binary search method, instead of computing the inflection point directly, you can find it using "quaternary search" over the
range [0, min(X, Y)/2]. To execute an iteration of quaternary search on the interval [a, b], compute V's value at h=(3a+b)/4 h=(2a+2b)/4,
and h=(a+3b)/4. Compute the second value minus the first value and the third value minus the second value. If the first difference is
greater, values of h less than (3a+b)/4 can be ruled out, and if the second difference is greater, values of h greater than (a+3b)/4 can
be ruled out. This process can be continued until the size of the range is less than a safe threshold (such as 10^-7). This range will
contain the inflection point if it is in [0, min(X, Y)/2] and it will contain min(X, Y)/2 otherwise. The interval from 0 up to the center
of this region thus is unimodal, has a monotonously decreasing derivative, and contains the desired value of h. Running binary search
on the derivative of this region as before will thus give the correct answer. This solution runs in O(lg((X+Y)/precision)) time.

Of course there are many other ways to solve this problem, inluding many other variations on the above ideas.
END ANNOTATION
*/

#include <math.h>
#include <iomanip>
#include <iostream>

using namespace std;

const double threshold = 1e-7;
const double epsilon = 1e-10;

double calculus(double X, double Y)
{
	double A = 12, B = -4 * (X + Y), C = X * Y;
	double h = (-B - sqrtl(B * B - 4 * A * C)) / (2 * A);
	double V = h * (X - 2 * h) * (Y - 2 * h);
	return V;
}

double binarySearchDirect(double X, double Y)
{
	double A = 12, B = -4 * (X + Y), C = X * Y;
	double lo = 0, hi = (X + Y) / 6;
	while (hi - lo >= threshold)
	{
		double h1 = (lo + hi) / 2;
		double dV = A * h1 * h1 + B * h1 + C;
		if (dV > 0) lo = h1;
		else hi = h1;
	}
	double h = (lo + hi) / 2;
	double V = h * (X - 2 * h) * (Y - 2 * h);
	return V;
}

double binarySearchEpsilon(double X, double Y)
{
	double lo = 0, hi = (X + Y) / 6;
	while (hi - lo >= threshold)
	{
		double h1 = (lo + hi) / 2;
		double h2 = h1 + epsilon;
		double V1 = h1 * (X - 2 * h1) * (Y - 2 * h1);
		double V2 = h2 * (X - 2 * h2) * (Y - 2 * h2);
		if (V2 > V1) lo = h1;
		else hi = h1;
	}
	double h = (lo + hi) / 2;
	double V = h * (X - 2 * h) * (Y - 2 * h);
	return V;
}

double ternarySearch(double X, double Y)
{
	double lo = 0, hi = min(X, Y) / 2;
	while (hi - lo >= threshold)
	{
		double h1 = (2 * lo + hi) / 3;
		double h2 = (lo + 2 * hi) / 3;
		double V1 = h1 * (X - 2 * h1) * (Y - 2 * h1);
		double V2 = h2 * (X - 2 * h2) * (Y - 2 * h2);
		if (V2 > V1) lo = h1;
		else hi = h2;
	}
	double h = (lo + hi) / 2;
	double V = h * (X - 2 * h) * (Y - 2 * h);
	return V;
}

double quaternarySearchDirect(double X, double Y)
{
	double A = 12, B = -4 * (X + Y), C = X * Y;
	double lo = 0, hi = min(X, Y) / 2;
	while (hi - lo >= threshold)
	{
		double h1 = (3 * lo + hi) / 4;
		double h2 = (lo + hi) / 2;
		double h3 = (lo + 3 * hi) / 4;
		double V1 = h1 * (X - 2 * h1) * (Y - 2 * h1);
		double V2 = h2 * (X - 2 * h2) * (Y - 2 * h2);
		double V3 = h3 * (X - 2 * h3) * (Y - 2 * h3);
		if (V3 - V2 > V2 - V1) lo = h1;
		else lo = h3;
	}
	
	hi = (lo + hi) / 2;
	lo = 0;
	while (hi - lo >= threshold)
	{
		double h1 = (lo + hi) / 2;
		double dV = A * h1 * h1 + B * h1 + C;
		if (dV > 0) lo = h1;
		else hi = h1;
	}
	double h = (lo + hi) / 2;
	double V = h * (X - 2 * h) * (Y - 2 * h);
	return V;
}

double quaternarySearchEpsilon(double X, double Y)
{
	double lo = 0, hi = min(X, Y) / 2;
	while (hi - lo >= threshold)
	{
		double h1 = (3 * lo + hi) / 4;
		double h2 = (lo + hi) / 2;
		double h3 = (lo + 3 * hi) / 4;
		double V1 = h1 * (X - 2 * h1) * (Y - 2 * h1);
		double V2 = h2 * (X - 2 * h2) * (Y - 2 * h2);
		double V3 = h3 * (X - 2 * h3) * (Y - 2 * h3);
		if (V3 - V2 > V2 - V1) lo = h1;
		else lo = h3;
	}

	hi = (lo + hi) / 2;
	lo = 0;
	while (hi - lo >= threshold)
	{
		double h1 = (lo + hi) / 2;
		double h2 = h1 + epsilon;
		double V1 = h1 * (X - 2 * h1) * (Y - 2 * h1);
		double V2 = h2 * (X - 2 * h2) * (Y - 2 * h2);
		if (V2 > V1) lo = h1;
		else hi = h1;
	}
	double h = (lo + hi) / 2;
	double V = h * (X - 2 * h) * (Y - 2 * h);
	return V;
}

int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		double X, Y;
		cin >> X >> Y;
		cout << fixed << setprecision(7) << calculus(X, Y) << endl;
		//cout << fixed << setprecision(7) << binarySearchDirect(X, Y) << endl;
		//cout << fixed << setprecision(7) << binarySearchEpsilon(X, Y) << endl;
		//cout << fixed << setprecision(7) << ternarySearch(X, Y) << endl;
		//cout << fixed << setprecision(7) << quaternarySearchDirect(X, Y) << endl;
		//cout << fixed << setprecision(7) << quaternarySearchEpsilon(X, Y) << endl;
	}
}