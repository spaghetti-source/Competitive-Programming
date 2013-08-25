// SPOJ 11354: Amusing numbers
// http://www.spoj.com/problems/TSHOW1/
//
// Solution: ad-hoc
//
// 5,6
// 55,56,65,66
// 555,556,565,566,655,656,665,666
// ...

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

void solve(LL n) {
  LL s = 0, t = 2;
  int k = 1;
  while (s + t < n) {
    s += t;
    t *= 2;
    ++k;
  }
  n -= (s+1);
  vector<int> u;
  while (k > 0) {
    --k;
    u.push_back(n % 2);
    n /= 2;
  }
  for (int i = u.size()-1; i >= 0; --i)
    printf("%c", "56"[u[i]]);
  printf("\n");
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    LL n; scanf("%lld", &n);
    solve(n);
  }
}
