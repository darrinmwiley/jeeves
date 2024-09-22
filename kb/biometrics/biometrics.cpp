/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/biometrics
TAGS: geometry
EXPLANATION:
We can translate each polygon so the first vertex is at (0, 0). Then we just need to determine if the polygons can be
scaled and rotated around the origin to each other. A fixed scale and rotation can be represented as a matrix. With the 
second vertexes of the polygons, we can determine this matrix, and then check if this matrix transforms every vertex
from the first polygon into the corresponding vertex in the second polygon

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
vector<pii> A, B;

istream& operator>>(istream& in, pii &a) {
	in >> a.first >> a.second;
	return in;
}

template<typename T>
istream& operator>>(istream& in, vector<T> &a) {
	for (T &v : a) in >> v;
	return in;
}

int sqD(pii a, pii b) {
	int f = (a.first - b.first);
	int s = (a.second - b.second);
	return f * f + s * s;
}

void process() {
	A = vector<pii>(N);
	B = vector<pii>(N);
	cin >> A >> B;

	for (int i = N-1; i >= 0; i--) {
		A[i].first -= A[0].first;
		A[i].second -= A[0].second;
		B[i].first -= B[0].first;
		B[i].second -= B[0].second;
	}

	int a = A[1].first*B[1].first + A[1].second*B[1].second;
	int b = A[1].first*B[1].second - A[1].second*B[1].first;
	int d = A[1].first*A[1].first + A[1].second*A[1].second;

	for (int i = 1; i < N; i++) {
		long long e1 = (long long)a*A[i].first - (long long)b*A[i].second;
		long long f1 = (long long)b*A[i].first + (long long)a*A[i].second;
		if ((long long)B[i].first*d != e1 || (long long)B[i].second * d != f1) {
			cout << "dissimilar\n";
			return;
		}
	}
	cout << "similar\n";
}

int main()
{
	cin >> N;
	while (N != 0) {
		process();
		cin >> N;
	}
	return 0;
}