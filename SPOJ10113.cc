// SPOJ 10113: Regular Convex Polygon
// http://www.spoj.com/problems/REGPOLYG/
//
// Solution: geometry

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <complex>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef complex<double> point;
const double PI = 4*atan(1.0);

double dot(point p, point q)   { return real(conj(p) * q); }
double cross(point p, point q) { return imag(conj(p) * q); }
double EPS = 1e-6;
int sign(double x) {
  if (x < -EPS) return -1;
  if (x > +EPS) return +1;
  return 0;
}

int main() {
  for (double x1, y1, x2, y2, x3, y3;
      scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3); ) {
    point p(x1, y1), q(x2, y2), r(x3, y3);

    double arg1 = ( arg(q - p) - arg(r - p)) / PI;
    double arg2 = ( arg(p - q) - arg(r - q)) / PI;
    
    int k = 3;
    for (; k <= 1000; ++k) {
      if (sign(arg1 * k - round(arg1 * k)) == 0 && 
          sign(arg2 * k - round(arg2 * k)) == 0) break;
    }
    printf("%d\n", k);
  }
}
