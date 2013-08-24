// SPOJ 5971: LCM Sum
// http://www.spoj.com/problems/LCMSUM/
//
// Solution: math (lcm-sum function)
//
// Theorem: 
//   lcm(1,n) + lcm(2,n) + ... + lcm(k,n)
// = n * (1 + \sum_{d|n} d phi(d)) / 2
// (see: https://cs.uwaterloo.ca/journals/JIS/VOL14/Toth/toth9.pdf )
//
// Let psi(n) := \sum_{d|n} d phi(d).
// Then we obtain 
//   psi(n) = psi(n/p) + p^k (p^k - p^{k-1}) psi(n/p^k).
//

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
LL f(int n) {
  const int N = 1000010;
  static int once, p[N], m[N], pm[N];
  static LL psi[N];
  if (!once++) {
    // factor table
    for (LL i = 1; i < N; ++i) p[i] = i;
    for (LL i = 2; i < N; ++i) 
      if (p[i] == i) {
        LL q = 1;
        for (int k = 1; (q *= i) < N; ++k) {
          for (int j = q; j < N; j += q) 
            p[j] = i, m[j] = k, pm[j] = q;
        }
      }
    psi[1] = 1;
    for (LL i = 2; i < N; ++i) 
      psi[i] = psi[i/p[i]] + pm[i]*(pm[i]-pm[i]/p[i])*psi[i/pm[i]];
  }
  return psi[n];
}


// === tick a time ===
#include <ctime>
double tick() {
  static clock_t oldtick;
  clock_t newtick = clock();
  double diff = 1.0*(newtick - oldtick) / CLOCKS_PER_SEC;
  oldtick = newtick;
  return diff;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    long long x = ((1 + f(n)) * n) / 2;
    printf("%lld\n", x);
  }
}
