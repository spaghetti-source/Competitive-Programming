// SPOJ 9921: ABC Path
// http://www.spoj.com/problems/ABCPATH/
//
// Solution: dfs

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

int h, w;
char B[200][200];

int dh[] = {1,1,0,-1,-1,-1,0,1}, 
    dw[] = {0,1,1,1,0,-1,-1,-1};
int dfs(int i, int j, char c) {
  if (i < 0 || j < 0 || i >= h || j >= w) return 0;
  if (B[i][j] != c) return 0;
  B[i][j] = 0;

  int ans = 0;
  for (int r = 0; r < 8; ++r) 
    ans = max(ans, dfs(i+dh[r], j+dw[r], c+1));
  return ans+1;
}

int solve() {
  vector< pair<char, pair<int,int> > > A;
  int ans = 0;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j) 
      ans = max(ans, dfs(i,j,'A'));
  return ans;
}

int main() {
  int T = 0;
  while (scanf("%d %d", &h, &w) == 2) {
    if (h == 0 && w == 0) break;
    for (int i = 0; i < h; ++i)
      scanf("%s", B[i]);
    printf("Case %d: %d\n", ++T, solve());
  }
}
