// SPOJ 13050: Entmoot
// http://www.spoj.com/problems/AMR12C/
//
// Solution: Geometry, Math (golden search)
// 
// Let fi(x,y) = ( (x-xi)^2 + (y-yi)^2 ) / si^2
// and f(x,y) = max fi(x,y)
//
// To avoid a numerical error, caused by
// large search range, apply golden search twice.

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)

#define SQ(x) ((x)*(x))

int n;
double px[100], py[100], s[100];

double f(double x, double y) {
  double ans = 0;
  REP(i, n) 
    ans = max(ans, sqrt(SQ((x-px[i])/s[i]) + SQ((y-py[i])/s[i])));
  return ans;
}

double g_a, g_d, g_c;
double g(double x) { // g(x) := min f(x,*)
  const double r = 2/(3+sqrt(5)), eps = 1e-7;
  double a = g_a, d = g_d;
  double b = a + (d-a)*r, c = d - (b-a);
  double fa = f(x,a), fb = f(x,b), fc = f(x,c), fd = f(x,d);
  while (d-a > eps) {
    if (fb < fc) { // min in [a,b,c) 
      d = c; c = b; fd = fc; fc = fb;
      b = a + (d - c); fb = f(x,b);
    } else {       // min in [b,c,d)
      a = b; b = c; fa = fb; fb = fc;
      c = d - (b - a); fc = f(x,c);
    }
  }
  g_c = c;
  return fc;
}
double h_a, h_d, h_c;
double h() {
  const double r = 2/(3+sqrt(5)), eps = 1e-8;
  double a = h_a, d = h_d;
  double b = a + (d-a)*r, c = d - (b-a);
  double fa = g(a), fb = g(b), fc = g(c), fd = g(d);
  while (d-a > eps) {
    if (fb < fc) { // min in [a,b,c) 
      d = c; c = b; fd = fc; fc = fb;
      b = a + (d - c); fb = g(b);
    } else {       // min in [b,c,d)
      a = b; b = c; fa = fb; fb = fc;
      c = d - (b - a); fc = g(c);
    }
  }
  h_c = c;
  return fc;
}
double solve() {
  h_a = g_a = -1000000; // approx solution
  h_d = g_d = +1000000;
  h();
  h_a = h_c-100; h_d = h_c+100; // optimal solution
  g_a = g_c-100; g_d = g_c+100;
  return h();
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    REP(i, n)
      scanf("%lf %lf %lf", &px[i], &py[i], &s[i]);
    printf("%.8lf\n", solve());
  }
}
