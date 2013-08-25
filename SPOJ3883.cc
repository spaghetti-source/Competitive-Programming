// SPOJ 3883: LATGACH3
// http://www.spoj.com/problems/M3TILE/
//
// Solution: DP
//
//   ___      ___      *__
// f(___) = f(**_) + f(*__)
//
//            ___      *__      ***
//        = f(**_) + f(***) + f(***)
//            g         h        f


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

typedef long long LL;

LL f(LL n);
LL g(LL n);
LL h(LL n) {
  static LL c[100];
  if (n == 0) return 0;
  if (n == 1) return 1;
  if (c[n]) return c[n];
  return c[n] = f(n-1) + g(n-1);
}
LL g(LL n) {
  if (n == 0) return 0;
  return h(n-1);
}
LL f(LL n) {
  static LL c[100];
  if (n == 0) return 1;
  if (n & 1) return 0;
  if (c[n]) return c[n];
  return c[n] = g(n) + h(n-1) + f(n-2);
}

int main() {
  for (LL n; scanf("%lld", &n) == 1; ) {
    if (n < 0) break;
    printf("%lld\n", f(n));
  }
}
