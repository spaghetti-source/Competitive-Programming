// SPOJ 9034: Help Tohu
// http://www.spoj.com/problems/TOHU/
//
// Solution: hand calculation

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int ncase;
  scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    double n; scanf("%lf", &n);
    double den = 4+3*n*(3+n);
    double num = 4*(1+n)*(2+n);
    printf("%.11f\n", den/num);
  }
}
