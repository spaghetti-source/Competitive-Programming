// SPOJ 1724: Counting Triangles
// http://www.spoj.com/problems/TRICOUNT/
//
// Solution: ad-hoc

#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
int main() {
  int T; scanf("%d", &T);
  while (T--) {
    LL n; scanf("%lld", &n);
    LL x = n*(n+2)*(2*n+1)/8;
    printf("%lld\n", x);
  }
}
