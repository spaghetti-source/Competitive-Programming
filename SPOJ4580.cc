// SPOJ 4580: ABCDEF
// http://www.spoj.com/problems/ABCDEF/
//
// Solution: sorting
//
// Note: long long 12.80[sec]
//       int        8.02[sec]
//
// Remark: We can sort s in O(n) time.
// but it is not necessary.
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;
int a[101], s[100*100*100+1], m;
int main() {
  int n; scanf("%d", &n);
  for (int i = 0; i < n; ++i) 
    scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i)
    if (a[i] != 0) 
      for (int j = 0; j < n; ++j)
        for (int k = 0; k < n; ++k)
          s[m++] = a[i] * (a[j] + a[k]);
  int cnt = 0;
  sort(s, s+m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      for (int k = 0; k < n; ++k) {
        pair<int*, int*> p = equal_range(s, s+m, a[i]*a[j]+a[k]);
        cnt += p.second - p.first;
      }
  printf("%d\n", cnt);
}
