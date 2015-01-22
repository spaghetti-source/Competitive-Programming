// SPOJ 7588: Wise And Miser
// http://www.spoj.com/problems/MISERMAN/
//
// Solution: dynamic programming

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);

  vector<vector<int>> T(n+1, vector<int>(m, 1<<29));
  for (int j = 0; j < m; ++j) T[0][j] = 0;
  // T[i][j] is a minimum cost at city i with id j

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      T[i+1][j] = min(T[i+1][j], T[i][j] + a[i][j]);
      if (j-1 >=   0) T[i+1][j] = min(T[i+1][j], T[i][j-1] + a[i][j-1]);
      if (j+1 <= n-1) T[i+1][j] = min(T[i+1][j], T[i][j+1] + a[i][j+1]);
    }
  }
  int ans = T[n][0];
  for (int j = 1; j < m; ++j)
    ans = min(ans, T[n][j]);
  printf("%d\n", ans);
}
