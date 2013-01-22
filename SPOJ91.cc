// SPOJ 91: Two squares or not two squares
// http://www.spoj.com/problems/TWOSQRS/
// 
// Solution: bi-monotone search
//
// Let L(x,y) = x^2 + y^2, which is bi-monotone.
// The problem is to find (x,y) s.t. L(x,y) == u.
// This can be done by bi-monotone search (windowing).
// 
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
LL N = 1000000000000LL;
LL S[1000010], T;

bool twoSumSqrs(LL u) {
  int i = 0, j = lower_bound(S,S+T,u)+1-S;
  while (i <= j) {
    if (S[i] + S[j] == u) return true;
    else if (S[i] + S[j] < u) ++i;
    else --j;
  }
  return false;
}

int main() {
  for (LL x = 0; x*x <= N; ++x)
    S[T++] = x*x;
  int T; scanf("%d", &T);
  for (int t = 0; t < T; ++t) {
    LL u; scanf("%lld", &u);
    if (twoSumSqrs(u)) printf("Yes\n");
    else printf("No\n");
  }
}
