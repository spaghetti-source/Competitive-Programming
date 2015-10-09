// SPOJ 19293: Galaxy distances
// http://www.spoj.com/problems/WPC5E/
//
// Solution: metric embedding
//
// Let p(i) := (i^2, -i^2, A(i)^2, -A(i)^2).
// Then dist(i,j) = |p(i) - p(j)|_infty.
//
// Farthest point pair in L_infty is easy to solve.
//
// in general, f(x) := <{+1,-1}^n, x> gives
// isometric embedding between L_1 to L_infty.
//
//
// (2 WAs because of `int i`)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

long long inf = (1ll << 62);

int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int n; scanf("%d", &n);
    long long minx, miny, minz, minw, maxx, maxy, maxz, maxw;
    minx = miny = minz = minw = inf;
    maxx = maxy = maxz = maxw = -inf;
    for (int i = 1; i <= n; ++i) {
      int a; scanf("%lld", &a);
      long long i2 = i; i2 *= i;
      long long a2 = a; a2 *= a;
      minx = min(minx, +i2+a2);
      maxx = max(maxx, +i2+a2);
      miny = min(miny, +i2-a2);
      maxy = max(maxy, +i2-a2);
      minz = min(minz, -i2+a2);
      maxz = max(maxz, -i2+a2);
      minw = min(minw, -i2-a2);
      maxw = max(maxw, -i2-a2);
    }
    printf("%lld\n", max({maxx-minx,maxy-miny,maxz-minz,maxw-minw}));
  }
}
