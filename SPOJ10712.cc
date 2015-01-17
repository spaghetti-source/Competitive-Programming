// SPOJ 10712: Easy Calculation
// http://www.spoj.com/problems/TRIGALGE/
//
// Solution: numerical analysis

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

template <class F, class G>
double find_root(F f, G df, double x) {
  for (int iter = 0; iter < 100; ++iter) {
    double fx = f(x), dfx = df(x);
    x -= fx/dfx;
    if (fabs(fx) < 1e-12) break;
  }
  return x;
}
void doit() {
  double a, b, c;
  scanf("%lf %lf %lf", &a, &b, &c);
  auto f = [&](double x) { return a * x + b * sin(x) - c; };
  auto df = [&](double x) { return a + b * cos(x); };
  double z = find_root(f, df, c/a);
  printf("%.6f\n", z + 1e-12);
}
int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) doit();
}
