/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/wrapping
TAGS: convex hull, shoelace theorem, trigonometry
EXPLANATION:
1/ Evaluate the coordinates of the rectangle after rotation by v degrees
2/ Use Graham Scan to build a convex hull from the coordinates
3/ Use Shoelace Theorem to find the area of the convex hull
4/ Evaluate the fraction between area of rectangle and area of convex hull
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define umap unordered_map
#define size(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "Yes": "No") << '\n'
#define printDecimal(d) cout << setprecision(9) << fixed << (d) << '\n'
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265

const ll inf = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(vector<T> arr) { for (int i = 0; i<size(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T> 
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }}

// Determine orientation of points
enum Orientation { CCL, CW, CCW };
Orientation findOrientation(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	int ret = (b.second - a.second) * (c.first - b.first) - (b.first - a.first) * (c.second - b.second);
	if (!ret) return CCL;
	return (ret > 0 ? CW : CCW);
}

// Shoelace Theorem to find area of convex hull
ld evaluate(vector<pair<ld, ld>> points) {
	ld ret = 0.0;
	for (int i = 0; i<size(points); i++) {
		ret += points[i].first * points[(i+1)%size(points)].second;
		ret -= points[i].second * points[(i+1)%size(points)].first;
	}
	return fabs(ret) / 2.0;
}

// Add coordinates to vector of points
void addShape(vector<pair<ld, ld>> &v, ld h, ld w) {
	vector<ld> x{0.0, w}, y{0.0, h};
	for (ld a : x) {
		for (ld b : y) {
			v.push_back(make_pair(a, b));
		}
	}
}

// Apply rotation on a point from a pivot
pair<ld, ld> rotatePoint(ld x, ld y, ld v, pair<ld, ld> vertice, pair<ld, ld> pivot) {
	ld new_x = vertice.first*cos(v) + vertice.second*sin(v) + x - pivot.first;
	ld new_y = vertice.first*sin(v) - vertice.second*cos(v) + y - pivot.second;
	return make_pair(new_x, new_y);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<pair<ld, ld>> points;
		ld total_area = 0;
		for (int i= 0; i<n; i++) {
			ld x,y,w,h,v; cin >> x >> y >> w >> h >> v;
			v = (-v)*PI/180;
			vector<pair<ld, ld>> vertices;
			addShape(vertices, h, w);
			pair<ld, ld> pivot = rotatePoint(x, y, v, make_pair(w/2, h/2), make_pair(x, y));
			for (int k = 0; k<4; k++) points.push_back(rotatePoint(x, y, v, vertices[k], pivot));
			total_area += h*w;
		}
		
		sort(points.begin(), points.end(), [](pair<ld, ld> a, pair<ld, ld> b) {
			if (a.first != b.first) return a.first < b.first;
			return a.second < b.second;
		});
		pair<ld, ld> left = points[0], right = points.back();
		vector<pair<ld, ld>> upper{left}, lower{left};
		
		for (int i = 1; i<size(points); i++) {
			Orientation curr = findOrientation(left, points[i], right);
			if (i == size(points)-1 || curr == CW) {
				if (size(upper) >= 2) {
					curr = findOrientation(upper[size(upper)-2], upper.back(), points[i]);
					while (size(upper) >= 2 && curr != CW) {
						upper.pop_back();
						if (size(upper) >= 2) curr = findOrientation(upper[size(upper)-2], upper.back(), points[i]);
					}
				}
				upper.push_back(points[i]);
			}
			if (i == size(points)-1 || curr == CCW) {
				if (size(lower) >= 2) {
					curr = findOrientation(lower[size(lower)-2], lower.back(), points[i]);
					while (size(lower) >= 2 && curr != CCW) {
						lower.pop_back();
						if (size(lower) >= 2) curr = findOrientation(lower[size(lower)-2], lower.back(), points[i]);
					}
				}
				lower.push_back(points[i]);
			}
		}
		for (int i = size(upper)-2; i>0; i--) lower.push_back(upper[i]);
		ld ret = total_area / evaluate(lower);
		cout << setprecision(1) << fixed << ret*100 << " %" << '\n';
	}
}  
