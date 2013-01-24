// SPOJ 6256 Inversion Count
// http://www.spoj.com/problems/INVCNT/
//
// Solution: sorting (inversion counting)
//
// Note: #inv = O(n^2), so long long is necessary.

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

#include <ctime>

using namespace std;
typedef long long LL;

// Merge sort with inversion counting
LL mergeSort(int a[], int n) {
  if (n <= 1) return 0;
  int m = n / 2, b[n];
  LL inv = mergeSort(a, m) + mergeSort(a+m, n-m);
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
  int t; scanf("%d", &t);
  while (t--) {
    int n; scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    printf("%lld\n", mergeSort(a, n));
  }

}
