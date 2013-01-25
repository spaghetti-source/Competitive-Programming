// SPOJ 346: Bytelandian gold coins
// http://www.spoj.com/problems/COINS/
//
// Solution: DP (partially cache)
//
// f(n) = max(n, f([n/2]) + f([n/3]) + f([n/4])),
// f(1) = 1, f(0) = 0.
//
// since 0 <= n <= 1,000,000,000, 
// we cannot cache f for all n.
// but after small recursion, n becomes small.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long LL;
LL f(LL n) {
  static const int N = 10000000;
  static LL cache[N];
  if (n <= 1) return n;
  if (n < N && cache[n] != 0) return cache[n];
  LL ans = max(n, f(n/2) + f(n/3) + f(n/4));
  if (n < N) cache[n] = ans;
  return ans;
}

int main() {
  int n; 
  while (scanf("%d", &n) == 1) 
    printf("%lld\n", f(n));
}
