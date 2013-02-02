// SPOJ 9722: Insertion Sort
//
// Solution: inversion counting
// (completely same as SPOJ 6256: Inversion Count)
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

// Merge sort with inversion counting
int mergeSort(int a[], int n) {
  if (n <= 1) return 0;
  int m = n / 2, b[n];
  int inv = mergeSort(a, m) + mergeSort(a+m, n-m);
  for (int i = 0, j = 0, k = m; j != m || k != n; ++i) {
    if      (j == m)       b[i] = a[k++];
    else if (k == n)       b[i] = a[j++];
    else if (a[j] <= a[k]) b[i] = a[j++];
    else                 { b[i] = a[k++]; inv += m-j; }
  }
  copy(b, b+n, a);
  return inv;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    printf("%d\n", mergeSort(a, n));
  }
}
