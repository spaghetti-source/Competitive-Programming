// SPOJ 7975: Tri graphs
// http://www.spoj.com/problems/ACPC10D/
//
// Solution: DP (shortest path on dag)
//

#include <iostream>
#include <cstdio>

using namespace std;

const int INF = 1 << 30;

int main() {
  int n, m = 1; 
  while (scanf("%d", &n), n != 0) {
    int a[n], b[n], c[n];
    for (int i = 0; i < n; ++i)
      scanf("%d %d %d", &a[i], &b[i], &c[i]);
    int x = INF, y = b[0], z = b[0] + c[0];
    for (int i = 1; i < n; ++i) {
      // x  y  z
      // s  t  u
      int s = a[i] + min(x, y),
          t = b[i] + min(x,min(y,min(z,s))),
          u = c[i] + min(t,min(y,z));
      swap(s, x); swap(t, y); swap(u, z);
    }
    printf("%d. %d\n", m++, y);
  }
}
