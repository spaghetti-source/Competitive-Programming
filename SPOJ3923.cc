// SPOJ 3923: Philosophiers Stone
// http://www.spoj.com/problems/BYTESM2/
//
// Solution: DP (shortest path on dag)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 1 << 28;
int m, n;
int x[200][200], s[2][200];
int solve() {
  for (int j = 1; j <= n; ++j)
    s[0][j] = x[0][j];
  for (int i = 1; i < m; ++i) {
    for (int j = 1; j <= n; ++j) 
      s[1][j] = x[i][j] + max(s[0][j-1], max(s[0][j], s[0][j+1]));
    for (int j = 1; j <= n; ++j) 
      swap(s[1][j], s[0][j]);
  }
  return *max_element(s[0]+1, s[0]+n+1);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    memset(x, 0, sizeof(x));
    memset(s, 0, sizeof(s));
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; ++i)
      for  (int j = 1; j <= n; ++j)
        scanf("%d", &x[i][j]);
    printf("%d\n", solve());
  }
}
