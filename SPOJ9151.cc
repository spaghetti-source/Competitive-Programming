// SPOJ 9151: Kids Love Candies
// http://www.spoj.com/problems/MIDOZ/
//
// Solution: trivial

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    int n, k, s = 0; scanf("%d %d\n", &n, &k);
    for (int i = 0; i < n; ++i) {
      int x; scanf("%d", &x); s += x / k;
    }
    printf("%d\n", s);
  }
}
