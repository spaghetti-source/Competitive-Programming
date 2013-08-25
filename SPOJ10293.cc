// SPOJ 10293: FANCY NUMBERS
// http://www.spoj.com/problems/FANCY/
//
// Solution: ad-hoc

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

LL solve(char s[]) {
  LL ans = 1;
  int k = 0;
  char c = 0, *p = s;
  do {
    if (*p != c) {
      ans *= (1ull << k);
      k = -1;
      c = *p;
    }
    ++k;
  } while (*p++ != 0);
  return ans;
}


int main() {
  char buf[256];
  gets(buf);
  int T = atoi(buf);
  while (T--) {
    gets(buf);
    printf("%lld\n", solve(buf));
  }
}
