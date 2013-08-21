// SPOJ 10235: Array Diversity
// http://www.spoj.com/problems/AMR11H/
//
// Solution: adhoc, sequence (windowing)
//
//
// substring:
//   Windowing technique;
//   Fix a left position. Extend window until it contains both min and max.
//   Then count all right-extended substrs, i.e., c += n - (r-1).
//
// subsequence:
//   Pick up at least one element in min elements ( 2^|min| - 1),
//   and at least one elments in max elements ( 2^|max| - 1),
//   and any number of elements in other elements( 2^|other| )
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
const LL M = 1000000007;

LL addMod(LL a, LL b, LL M) {
  a += b;
  while (a >= M) a -= M;
  return a;
}
LL subMod(LL a, LL b, LL M) { 
  while (a < b) a += M;
  return a - b;
}
LL mulMod(LL a, LL b, LL M) {
  LL r = a*b - LL(double(a)*b/M + 0.5)*M;
  while (r < 0) r += M;
  return r;
}
LL powMod(LL a, LL b, LL M) {
  LL x = 1;
  for (; b > 0; b >>= 1) {
    if (b & 1) x = mulMod(x, a, M);
    a = mulMod(a, a, M);
  }
  return x;
}

LL substr(vector<int> a) {
  LL ans = 0;
  int n = a.size();
  int minval = *min_element(ALL(a)), maxval = *max_element(ALL(a));
  int mincnt = 0, maxcnt = 0;
  for (int l = 0, r = 0; l < n; ++l) {
    while (r < n && (mincnt == 0 || maxcnt == 0)) {
      if (a[r] == minval) ++mincnt;
      if (a[r] == maxval) ++maxcnt;
      ++r;
    }
    if (mincnt && maxcnt) ans = addMod(ans, n - r + 1, M);
    if (a[l] == minval) --mincnt;
    if (a[l] == maxval) --maxcnt;
  }
  return ans;
}
LL subseq(vector<int> a) {
  LL ans = 0;
  int n = a.size();
  int minval = *min_element(ALL(a)), maxval = *max_element(ALL(a));
  if (minval == maxval) return subMod(powMod(2, n, M), 1, M);
  int mincnt = count(ALL(a), minval), maxcnt = count(ALL(a), maxval);
  return mulMod(mulMod(subMod(powMod(2, maxcnt, M), 1, M),
                       subMod(powMod(2, mincnt, M), 1, M), M),
                powMod(2, n-maxcnt-mincnt, M), M);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    vector<int> a(n);
    REP(i, n) scanf("%d", &a[i]);
    printf("%lld %lld\n", substr(a), subseq(a));
  }
}
