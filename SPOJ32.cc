// SPOJ 32: A Needle in the Haystack
// http://www.spoj.com/problems/NHAY/
//
// Solution: string matching in stream (KMP)

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


void solve(int n) {
  char p[n]; 
  scanf("%s\n", p);
  // KMP table
  int f[n+1], j = f[0] = -1;
  for (int i = 1; i <= n; ++i) {
    while (j >= 0 && p[j] != p[i-1]) j = f[j];
    f[i] = ++j;
  }

  int count = 0;
  for (int i = 0, k = 0; ; ++i) {
    char c = getchar();
    if (c == '\n') break;
    while (k >= 0 && p[k] != c) k = f[k];
    if (++k >= n) {
      printf("%d\n", i-n+1);
      ++count;
      k = f[k];
    }
  }
  if (count == 0) printf("\n");
}

int main() {
  for (int n; scanf("%d\n", &n) == 1 ;) {
    solve(n);
  }
}
