// SPOJ 8985: Line up
// http://www.spoj.com/problems/KOILINE/
//
// Solution: Sorting (order statistics)
//
// Let S be a sorted list of heights
// for i = n, n-1, ..., 1
//   output s[i]+1'th item in S
//   remove s[i]+1'th item from S
//
// To implement S, we can use binary indexed tree.

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

#include <ctime>

using namespace std;

// Removable array by binary indexed tree
typedef long long LL;
struct RemovableArray {
  vector<LL> a;
  vector<int> m;
  void build(int t, int l, int r) {
    if (l + 1 == r) m[t] = 1;
    else if (l + 1 < r) {
      build(2*t+1, l, (l+r)/2);
      build(2*t+2, (l+r)/2, r);
      m[t] = m[2*t+1] + m[2*t+2];
    }
  }
  RemovableArray(vector<LL> a_) : a(a_), m(4*a_.size()) {
    build(0, 0, a.size());
  }
  LL &kth(int t, int k, int l, int r) {
    if (l + 1 == r) return a[l];
    if (m[2*t+1] >= k) return kth(2*t+1, k, l, (l+r)/2);
    else return kth(2*t+2, k - m[2*t+1], (l+r)/2, r);
  }
  void remove(int t, int k, int l, int r) {
    if (l + 1 == r) m[t] = 0;
    else if (l + 1 < r) {
      if (m[2*t+1] >= k) remove(2*t+1, k, l, (l+r)/2);
      else remove(2*t+2, k-m[2*t+1], (l+r)/2, r);
      m[t] = m[2*t+1] + m[2*t+2];
    }
  }
  LL &kth(int k) { return kth(0, k, 0, a.size()); }
  void remove(int k) { return remove(0, k, 0, a.size()); }
};

int main() {
  int n; scanf("%d", &n);
  vector<LL> a(n);
  for (int i = 0; i < n; ++i) 
    scanf("%lld", &a[i]);
  sort(a.begin(), a.end());
  RemovableArray T(a);

  vector<int> s(n);
  for (int i = 0; i < n; ++i) 
    scanf("%d", &s[i]);

  vector<LL> out;
  for (int i = n-1; i >= 0; --i) {
    out.push_back( T.kth(s[i]+1) );
    T.remove( s[i]+1 );
  }
  for (int i = n-1; i >= 0; --i) 
    printf("%lld\n", out[i]);
}
