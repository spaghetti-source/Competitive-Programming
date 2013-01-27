// SPOJ 7718: Number of common divisors
//
// Solution: Math
//
// g = gcd(x,y) = p^e1 p^e2 ... 
// -> return e1 e2 ... 
//
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)

typedef long long LL;

LL gcd(LL a, LL b) {
  for (; a; swap(b %= a, a));
  return b;
}

const int N = 1000010;
int s[N], d[N];
int main() {
  for (int i = 0; i < N; ++i) 
    d[i] = i;

  for (int i = 2; i*i < N; ++i) 
    if (d[i] == i) 
      for (int j = i+i; j < N; j+=i)
        d[j] = min(d[j], i);

  int T; scanf("%d", &T);
  while (T--) {
    LL x, y; scanf("%lld %lld", &x, &y);
    LL g = gcd(x,y);

    int k = 1;
    while (g > 1) {
      int s = 1;
      int p = d[g];
      while (g % p == 0) {
        ++s;
        g /= p;
      }
      k *= s;
    }
    printf("%d\n", k);
  }
}
// 100000 = 10^5 = 2^5 5^5
//
