/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/dartboard
TAGS: math, calculus, geometry
EXPLANATION:
for each ring, integrate over the length of the ring f(dist) * area to calculate the total probability of hitting it, then multiply by the average score of that ring.
I wasn't good enough at calculus so I just used Reimann sums with very small step size.
END ANNOTATION
*/
#include <iostream>
#define _USE_MATH_DEFINES

#include <cmath>
using namespace std;

    double reimann(double r1, double r2, double stdev)
    {
        double area = M_PI*r2*r2 - M_PI*r1*r1;
        double r = (r1+r2)/2;
        double prob = 1/(2*M_PI*stdev*stdev)*exp(-r*r/(2*stdev*stdev));
        return prob*area;
    }

    double integrate(double r1, double r2, double stdev)
    {
        double sum = 0;
        double step = .000005;
        for(double i = r1;i<r2;i+=step)
        {
            sum += reimann(i,i+step, stdev);
        }
        return sum;
    }

int main() {
    double bullsEyeRadii, bullRadii, innerRing, triple, outerRing, doub, stdev;
    cin >> bullsEyeRadii >> bullRadii >> innerRing >> triple >> outerRing >> doub >> stdev;
    double average_pie = 10.5;
    double score = 0;
    score += 50 * integrate(0,bullsEyeRadii, stdev);
    score += 25 * integrate(bullsEyeRadii, bullRadii, stdev);
    score += average_pie * integrate(bullRadii, innerRing, stdev);
    score += 3 * average_pie * integrate(innerRing, triple, stdev);
    score += average_pie * integrate(triple, outerRing, stdev);
    score += 2 * average_pie * integrate(outerRing, doub, stdev);
    cout << score;
}
