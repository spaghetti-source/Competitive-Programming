// SPOJ 5084: Discrete Math Problem
// http://www.spoj.com/problems/GCD3/
//
// Solution: math
//
// By simple calculation we have
//   (a+b, a^2+b^2-ab(2^k-2)) = (a+b, a^2 2^k).
// Since a+b and a^2 are coprime, 
//   gcd(M,N) = 2^m where 2^m | M.
//
// We use the relation to check the divisibility efficiently:
//   2^m | M iff 2^m | (M mod 10^k)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
LL solve() {
  char s[210];
  int k;
  scanf("%s %*s %d", s, &k);
  int len = strlen(s);
  LL x, ans = 1;
  int i = min(len, k);
  sscanf(&s[len-i], "%lld", &x);
  while (i > 0 && x % 2 == 0) {
    --i;
    x /= 2;
    ans *= 2;
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) printf("%lld\n", solve());
}
