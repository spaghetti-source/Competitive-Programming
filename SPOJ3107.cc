// SPOJ 3107: Odd Number of Divisors
// http://www.spoj.com/problems/ODDDIV/
//
// Solution: math, binary search
//
// x has odd number of divisors iff x is squared number.
// So, we first enumerate all squared number,
// bucket them by the number of divisors, and binary search.

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

typedef long long LL;
unordered_map<int, vector<LL> > a;

// number of divisors of x*x
LL divisors(LL x) {
  LL ans = 1;
  for (LL y = 2; y*y <= x; ++y) {
    if (x % y == 0) {
      LL c = 0;
      while (x % y == 0) {
        x /= y;
        ++c;
      }
      ans *= (2*c+1);
    }
  }
  if (x > 1) ans *= 3;
  return ans;
}
void init() {
  for (LL x = 1; x*x < 10000000000ll; ++x) 
    a[divisors(x)].push_back(x*x);
}
LL solve(int k, LL lo, LL hi) {
  return upper_bound(ALL(a[k]), hi) - lower_bound(ALL(a[k]), lo);
}

int main() {
  init();
  int T; scanf("%d", &T);
  while (T--) {
    int k;
    LL lo, hi;
    scanf("%d %lld %lld", &k, &lo, &hi);
    printf("%lld\n", solve(k, lo, hi));
  }
}
