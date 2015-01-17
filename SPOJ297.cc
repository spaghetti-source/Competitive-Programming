// SPOJ 297: Aggressive Cows
// http://www.spoj.com/problems/AGGRCOW/
//
// Solution: binary search
//
// Let f(d) = true  if there is >= d placement,
//            false otherwise.
// Then f is monotone decreasing with respect to d, and 
// the solution is the maximum d with f(d) == true.

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define fst first
#define snd second
#define all(c) c.begin(), c.end()

int f(const vector<int> &a, int d) {
  int c = 1, j = 0;
  for (int i = 1; i < a.size(); ++i) 
    if (a[i] - a[j] >= d) { j = i; ++c; }
  return c;
}
int main() {
  int ncase;
  scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    sort(all(a));
    int lo = 1, hi = a.back()+1;
    while (hi - lo >= 2) { // f(lo) >= m, and f(hi) < m
      int mid = (lo + hi) / 2;
      int s = f(a, mid);
      if (s >= m) lo = mid; else hi = mid;
    }
    printf("%d\n", lo);
  }
}
