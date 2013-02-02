// SPOJ 7973: Sometimes, a penalty is good!
// http://www.spoj.com/problems/ACPC10E/
//
// Solution: Ad-hoc
//
// Unreadable problem text :(

#include <cstdio>

using namespace std;

typedef long long LL;
LL f(LL n) {
  LL m = 1;
  while (m < n) m *= 2;
  return m; // smallest pow of 2, greater than or equal to n
}

int main() {
  LL G, T, A, D;
  while (scanf("%lld %lld %lld %lld", &G, &T, &A, &D), G > 0) {
    LL m = G * T * (T-1) / 2; // group stage match
    LL n = G * A + D; // teams advance to KO stage
    LL e = f(n) - n; // extra teams needed
    n += e;
    m += n-1; // number of matches on a tornament
    printf("%lld*%lld/%lld+%lld=%lld+%lld\n", G,A,T,D,m,e);
  }
}
