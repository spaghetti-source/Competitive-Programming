// SPOJ 10373: Help Balaji!
// http://www.spoj.com/problems/ABA12A/
//
// Solution: trivial
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;
typedef long long LL;
int main() {
  int c; scanf("%d", &c);
  while (c--) {
    LL a, b; scanf("%lld %lld", &a, &b);
    printf("%lld\n", b);
  }
}
