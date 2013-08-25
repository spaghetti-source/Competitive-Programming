// SPOJ 2716: Maximal Quadrilateral Area
// http://www.spoj.com/problems/QUADAREA/
//
// Solution: elementary math (Brahmagupta's formula)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

typedef long long LL;
const LL M = 1000000007;
int main() {
  int T; scanf("%d", &T);
  while (T--) {
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    double s = (a+b+c+d) / 2;
    double S = sqrt((s-a)*(s-b)*(s-c)*(s-d));
    printf("%.2lf\n", S);
  }
}
