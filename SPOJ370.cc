// SPOJ 370: Ones and zeros
// http://www.spoj.com/problems/ONEZERO/
//
// solution: BFS (the number of states is at most x).

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

#define fst first
#define snd second
#define all(c) c.begin(), c.end()

void solve(int x) {
  if (x <= 1) {
    printf("%d\n", x);
    return;
  }
  vector<int> prev(x), path(x);
  queue<int> que;
  que.push(1);
  prev[1] = -1;
  path[1] =  1;
  while (!que.empty() && prev[0] == 0) {
    int a = que.front(); que.pop();
    for (int d = 0; d <= 1; ++d) {
      int b = (10 * a + d) % x;
      if (prev[b] == 0) {
        prev[b] = a;
        path[b] = d;
        que.push(b);
      }
    }
  }
  vector<int> ans;
  for (int a = 0; a >= 0; a = prev[a]) 
    ans.push_back(path[a]);
  for (int i = ans.size()-1; i >= 0; --i)
    printf("%d", ans[i]);
  printf("\n");
}

int main() {
  int ncase;
  scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int x;
    scanf("%d", &x);
    solve(x);
  }
}
