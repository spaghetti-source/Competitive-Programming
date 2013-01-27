// SPOJ 12407: Johnny The Gambler
//
// Solution: Bucket
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)

typedef long long LL;

const int N = 1010;
int a[100100], C[N];

int getint() {
  char c = getchar();
  while (c < '0' || c > '9') c = getchar();
  int x = 0;
  do {
    x = 10*x + c-'0';
    c = getchar(); 
  } while (c >= '0' && c <= '9');
  return x;
}

int main() {
  int T = getint();
  for (int t = 1; t <= T; ++t) {
    int x = getint();
    int n = getint();
    for (int i = 0; i < n; ++i)
      a[i] = getint();

    memset(C, 0, sizeof(C));
    LL total = 0;
    for (int i = n-1; i >= 0; --i) {
      if (0 <= x-a[i] && x-a[i] < N)
        total += C[ x - a[i] ];
      ++C[ a[i] ];
    }
    printf("%d. %lld\n", t, total);
  }
}
