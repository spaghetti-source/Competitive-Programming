// SPOJ 8372: Triple Sums
// http://www.spoj.com/problems/TSUM/
//
// Solution: FFT (fast polynomial multiplication)
//
// Let 
//   p(x) = \sum x^{a(i)}
//   q(x) = \sum x^{a(i)+a(i)}
//   r(x) = \sum x^{a(i)+a(i)+a(i)}
// Then 
//   p^3 - 3 p q + 2 r
// is a solution.

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <complex>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef complex<double> C;
void fft(vector<C> &a, int sign = 1) {
  int n = a.size(); // n should be a power of two
  double theta = 8 * sign * atan(1.0) / n; 
  for (int i = 0, j = 1; j < n - 1; ++j) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  for (int m, mh = 1; (m = mh << 1) <= n; mh = m) {
    int irev = 0;
    for (int i = 0; i < n; i += m) {
      C w = exp(C(0, theta*irev));
      for (int k = n >> 2; k > (irev ^= k); k >>= 1);
      for (int j = i; j < mh + i; ++j) {
        int k = j + mh;
        C x = a[j] - a[k];
        a[j] += a[k];
        a[k] = w * x;
      }
    }
  }
}

int main() {
  int n; 
  scanf("%d", &n);
  vector<int> x(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &x[i]);
  int pow2 = 1 << 17;

  vector<C> p(pow2), q(pow2), r(pow2);
  for (int i = 0; i < n; ++i) { 
    int e = x[i] + 20000;
    p[e]   += 1;
    q[2*e] += 1;
    r[3*e] += 1;
  }
  fft(p);
  fft(q);
  vector<C> s(pow2);
  for (int i = 0; i < pow2; ++i) 
    s[i] = p[i]*p[i]*p[i] - 3.0*p[i]*q[i];
  fft(s, -1);

  for (int i = 0; i < pow2; ++i) {
    double ans = round((real(s[i]) / pow2 + 2 * real(r[i])) / 6);
    if (ans > 0) 
      printf("%d : %.0lf\n", i - 60000, ans);
  }
}
