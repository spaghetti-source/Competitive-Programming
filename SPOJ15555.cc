// SPOJ 15555: Check the coprimeness
// http://www.spoj.com/problems/IITKWPCB/
//
// Solution: math(gcd)

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
LL gcd(LL a, LL b) {
  for (; a; swap(b %= a, a));
  return b;
}
LL solve(LL n) {
  LL m;
  for (m = n/2; m > 0; --m)
    if (gcd(m,n) == 1) break;
  return m;
}

int main() {
  int T; cin >> T;
  while (T--) {
    LL n; cin >> n;
    cout << solve(n) << endl;
  }
}
