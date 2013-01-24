// SPOJ 2742: Summing Sums
// http://www.spoj.com/problems/SUMSUMS/
//
// Solution: Math
//
//   x(k) = (J - I)^k x(0)
//
// Let (J - I)^k =: a(k) J + b(k) I. THen
//   ( a(k) J + b(k) I )( J - I ) 
//  = a(k) J^2 - a(k) J + b(k) J + b(k) I
//  = ( (n - 1) a(k) + b(k) ) - b(k)
//
//    a(k+1) = (n - 1) a(k) - b(k)
//    b(k+1) = -b(k)
//
// Solve this, we obtain
//
//   a(k) = (t^k - (-1)^k) / (t + 1)
//   b(k) = (-1)^k

#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;
LL M = 98765431;

LL addMod(LL a, LL b, LL M) {
  return (a += b) < M ? a : a - M;
}
LL mulMod(LL a, LL b, LL M) {
  LL x = 0;
  for (; b > 0; b >>= 1) {
    if (b & 1) x = addMod(x, a, M);
    a = addMod(a, a, M);
  }
  return x;
}
LL powMod(LL a, LL b, LL M) {
  LL x = 1;
  for (; b > 0; b >>= 1) {
    if (b & 1) x = mulMod(x, a, M);
    a = mulMod(a, a, M);
  }
  return x;
}
LL divMod(LL a, LL b, LL M) {
  LL u = 1, x = 0, s = b, t = M; // compute with LL
  while (s) {
    LL q = t / s;
    swap(x -= u * q, u);
    swap(t -= s * q, s);
  }
  return mulMod(x < 0 ? x + M : x, a / t, M);
}

int main() {
  LL n, k;
  scanf("%lld %lld", &n, &k);

  LL b = (k % 2 == 0) ? 1 : M-1;
  LL s = powMod(n-1, k, M) - b;
  if (s < 0) s += M;
  LL a = divMod(s, n, M);

  LL x[n], sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &x[i]);
    sum += x[i];
    while (sum >= M) sum -= M;
  }
  for (int i = 0; i < n; ++i) {
    printf("%lld\n", addMod(mulMod(sum,a,M),mulMod(x[i],b,M),M));
  }
}
