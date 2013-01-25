// SPOJ 744: Longest Permutation
// http://www.spoj.com/problems/LPERMUT/
//
// Solution: Ad-Hoc
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

typedef long long LL;
int n, a[100002], lim[100002], cnt[100002];
LL s[100002];

// (1) lim: 
//   a[i] ... a[ lim[i]-1 ] are distinct
//
// (2) s[i] := a[0,i]
//   { a[i] ... a[i+w] } = { 1 ... w } iff 
//     - a[i], ..., a[i+w] are distinct
//     - 2 (a[i] + ... a[i+w]) == (1 + w) w
//
//  Remark: sum is not fit in 2^31.
//
inline void init() {
  int m = n-1;
  for (int i = n-1; i >= 0; --i) {
    ++cnt[ a[i] ];
    while (cnt[ a[i] ] > 1) 
      cnt[a[m--]]--;
    lim[i] = m+1;
  }
}

inline int solve() {
  init();
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i+ans+1; j <= lim[i]; ) {
      LL w = j - i;
      LL x = 2 * (s[j] - s[i]) - (w+1) * w;
      if (x == 0) { ans = w; ++j; }
      else { j += x/(2*w) + (x%(2*w) > 0); }
    }
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    s[i+1] = s[i] + a[i];
  }
  printf("%d\n", solve());
}
