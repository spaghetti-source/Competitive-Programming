// SPOJ 9508: Magic Bitwise And Operation
// http://www.spoj.com/problems/AND/
//
// Solution: exhaustive search with plunning

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

typedef unsigned long long ULL;
int n, k;
ULL a[50], b[50];
void solve(int p, int l, ULL x, ULL &z) {
  z = min(z, x);
  if (l == k || p == n) return;
  if ((x & b[p]) >= z) return;
  solve(p+1, l+1, x & a[p], z);
  solve(p+1, l  , x       , z);
}
int main() {
  int T; scanf("%d", &T);
  REP(t, T) {
    scanf("%d %d", &n, &k);
    REP(i, n) scanf("%llu", &a[i]);
    sort(a, a+n);
    b[n-1] = a[n-1];
    for (int i = n-2; i >= 0; --i) b[i] = a[i] & b[i+1];
    ULL opt = a[0];
    solve(0, 0, -1, opt);
    printf("Case #%d: %llu\n", t+1, opt);
  }
}

