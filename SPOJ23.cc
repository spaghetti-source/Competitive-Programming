// SPOJ 23: Pyramids
// http://www.spoj.com/problems/PIR
//
// Solution: Geometry (Cayley-Menger determinant)
//
// 2^n n! vol = det (v1 
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

#include <cmath>

double disp(double x[], int m, int n = -1) {
  if (n < 0) n = m;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%.3lf ", x[n*i+j]);
    }
    printf("\n");
  }
  printf("\n");
}

// i: 縦 
// j: 横
double det(double x[], int n) {
  double d = 1;
  REP(i,n) {
    int p = i; // pivot 
    for (int k = i+1; k < n; ++k)
      if (fabs(x[n*k+i]) > fabs(x[n*p+i])) p = k;
    if (fabs(x[n*p+i]) < 1e-8) return 0;
    for (int j = i; j < n; ++j)
      swap(x[n*i+j], x[n*p+j]);
    d *= x[n*i+i];
    for (int k = i+1; k < n; ++k) { // x[k] -= x[i] * x[k][i]/x[i][i]
      for (int j = i+1; j < n; ++j) 
        x[n*k+j] -= x[n*i+j] * x[n*k+i] / x[n*i+i];
    }
  }
  return d;
}

// 2^n n! V^2 = det D
double vol(double d12, double d13, double d14,
           double d23, double d24, double d34) {
  d12*=d12; d13*=d13; d14*=d14; d23*=d23; d24*=d24; d34*=d34;
  double x[] ={0,  1,  1,  1,  1,
               1,  0,d12,d13,d14,
               1,d12,  0,d23,d24,
               1,d13,d23,  0,d34,
               1,d14,d24,d34,  0};
  return sqrt(fabs(det(x, 5))/288);

}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    double d12, d13, d14, d23, d24, d34;
    scanf("%lf%lf%lf%lf%lf%lf", &d12,&d13,&d14,&d23,&d24,&d34);
    printf("%.4lf\n", vol(d12,d13,d14,d23,d24,d34));
  }
}
