/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/kinversions
TAGS: FFT
EXPLANATION: 
* You can represent the string as two polynomials for B and A
* If a character is B, let that be a term in B's polynomial, and vice versa
* Let the powers for the B polynomial increase from the left, and from the right for A
* Example - BABA ==> B_B_ ==> (x^3 + 0 + x + 0)
*                ==> _A_A ==> (0 + x + 0 + x^3)
* 
* We see that when we multiply the polynomials, terms the same distance apart
* in the string get added to the same term. More exactly x^(N-1+i) is the number
* of pairs distance i apart.
* 
* FFT is used to efficiently multiply polynomials
END ANNOTATION
*/

//Suraj Mathashery

#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <iomanip>
#include <string>

using namespace std;


//FFT code from kactl
typedef complex<double> C;
typedef vector<double> vd;
typedef vector<int> vi;
void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for(int i = k; i < 2*k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for(int j = 0; j < k; j++) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(a.size() + b.size() - 1);
	int L = 32 - __builtin_clz(res.size()), n = 1 << L;
	vector<C> in(n), out(n);
	copy(begin(a), end(a), begin(in));
	for(int i = 0; i < b.size(); i++) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	for(int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	for(int i = 0; i < res.size(); i++) res[i] = imag(out[i]) / (4 * n);
	return res;
}

vi conv(const vi& a, const vi& b){
	vd da(a.size());
	vd db(b.size());
	for(int i = 0; i < a.size(); i++) da[i] = (double) a[i];
	for(int i = 0; i < b.size(); i++) db[i] = (double) b[i];
	
	vd dr = conv(da, db);
	vi res(dr.size());
	for(int i = 0; i < res.size(); i++){
		res[i] = (int) (dr[i]+0.5);
	}
	return res;
}

int main(){
	string s;
	cin >> s;
	int N = s.size();
	
	vi B(N), A(N);
	for(int i = 0; i < N; i++){
		if(s[i] == 'A'){
			A[i] = 1;
		}
		else{
			B[N-1-i] = 1;
		}
	}
	
	vi res = conv(B, A);
	
	for(int i = N; i < 2*N-1; i++){
		cout << res[i] << endl;
	}
	
	return 0;
}
