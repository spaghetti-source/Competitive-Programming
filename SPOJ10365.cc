// SPOJ 10365: PICK UP DROP ESCAPE
//
// Solution: exhaustive search

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;


int n, k;
int x[100];
const int INF = 1 << 30;
int solve(int i, int l, int y) {
  if (i == n) 
    return l == k ? y : -INF;
  int t = solve(i+1, l, y);
  if (l < k) t = max(t, solve(i+1, l+1, y ^ x[i]));
  return t;
}
int main() {
  int t; scanf("%d", &t);
  while (t--) {
    scanf("%d %d\n", &n, &k);
    for (int i = 0; i < n; ++i)
      scanf("%d", &x[i]);
    printf("%d\n", solve(0,0,0));
  }
}
