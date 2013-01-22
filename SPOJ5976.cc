// SPOJ 5976 Traversing Grid
// http://www.spoj.com/problems/TRGRID/
// 
// Solution: Ad-Hoc

#include <cstdio>
#include <iostream>

using namespace std;

int main() {
  int T; scanf("%d", &T);
  for (int t = 0; t < T; ++t) {
    int m, n; scanf("%d %d", &m, &n);
    int q = (min(m,n)-1) / 2; 
    m -= 2*q; n -= 2*q;
    if (m == 1) printf("R\n");
    else if (n == 1) printf("D\n");
    else if (m == 2) printf("L\n");
    else printf("U\n");
    /*
     *    *>>>>>
     *    ^*   v
     *    ^    v
     *    <<<<<<
     *
     *   f(m,n) = f(m-2,n-2)
     *   f(1,n) = R
     *   f(m,1) = D
     *   f(2,n) = L
     *   f(m,2) = U
     *
     */
  }
}
