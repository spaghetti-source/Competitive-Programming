// SPOJ 379: Ambiguous Permutation
// http://www.spoj.com/problems/PERMUT2/
//
// Solution: trivial

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  for (int n; scanf("%d", &n) == 1 && n != 0; ) {
    int a[n], b[n];
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      b[--a[i]] = i;
    }
    bool eq = true;
    for (int i = 0; eq && i < n; ++i)
      if (a[i] != b[i]) eq = false;
    if (eq) printf("ambiguous\n");
    else    printf("not ambiguous\n");
  }
}
