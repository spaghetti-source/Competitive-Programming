// SPOJ 13388: Easy Jug
//
// Solution: Math (gcd)

#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;
LL gcd(LL a, LL b) {
  for (; a; swap(b %= a, a));
  return b;
}
bool solve(LL x, LL y, LL z) {
  if (max(x,y) < z) return false;
  return z % gcd(x,y) == 0;
}
int main() {
  int T; scanf("%d", &T);
  while (T--) {
    LL x, y, z; scanf("%lld %lld %lld", &x, &y, &z);
    printf("%s\n", solve(x,y,z) ? "YES" : "NO");
  }
}
