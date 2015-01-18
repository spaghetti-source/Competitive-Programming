// SPOJ 3266: K-query
// http://www.spoj.com/problems/KQUERY/
//
// Solution: query reordering + fenwick tree
//
// For decreasing order in k, 
//   1) report x[i] + ... + x[j]
//   2) x[i] += 1 for all a[i] >= k

#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define all(c) c.begin(), c.end()

template <class T>
struct fenwick_tree {
  vector<T> x;
  fenwick_tree(int n, T a = T(0)) : x(n, a) { }
  void add(int k, int a) { // x[k] += a
    for (; k < x.size(); k |= k+1) x[k] += a;
  }
  T sum(int k) { // return x[0] + ... + x[k]
    T s = 0;
    for (; k >= 0; k = (k&(k+1))-1) s += x[k];
    return s;
  }
};

int main() {

  struct event {
    int id; // -1 for 'set', >= 0 for query
    int k, i, j;
    bool operator < (const event& e) const {
      if (k != e.k) return k < e.k;
      return id < e.id;
    }
  };
  vector<event> es;

  int n; scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int a; scanf("%d", &a);
    es.push_back({-1, a, i});
  }
  int q; scanf("%d", &q);
  for (int t = 0; t < q; ++t) {
    int i, j, k; scanf("%d %d %d", &i, &j, &k); --i; --j;
    es.push_back({t, k, i, j});
  }
  sort(all(es));
  reverse(all(es));

  vector<int> ans(q);
  fenwick_tree<int> T(n);
  for (auto e: es) {
    if (e.id < 0) T.add(e.i, 1);
    else ans[e.id] = T.sum(e.j) - T.sum(e.i-1);
  }
  for (int t = 0; t < q; ++t) 
    printf("%d\n", ans[t]);
}
