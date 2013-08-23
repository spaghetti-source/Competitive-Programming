// SPOJ 9734: Hacking the random number generator
// http://www.spoj.com/problems/HACKRNDM/
//
// Solution: sorting

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

int solve(vector<int> a, int k) {
  int n = a.size();
  int ans = 0;
  sort(ALL(a));
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n && a[j] - a[i] < k) ++j;
    if (a[j] - a[i] < k) break;
    if (a[j] - a[i] == k) ++ans;
  }
  return ans;
}

int main() {
  int n, k; scanf("%d %d", &n, &k);
  vector<int> a(n);
  REP(i, n) scanf("%d", &a[i]);
  printf("%d\n", solve(a, k));
}
