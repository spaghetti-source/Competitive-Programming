// SPOJ 3267: D-query
// http://www.spoj.com/problems/DQUERY/
//
// Solution: query reordering, fenwick tree

#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

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
  int n; scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  int q; scanf("%d", &q);
  struct query { int i, j, k; };
  unordered_map<int, vector<query>> queries;
  for (int k = 0; k < q; ++k) {
    int i, j; scanf("%d %d", &i, &j); --i; --j;
    queries[j].push_back({i, j, k});
  }
  vector<int> ans(q);

  // x[i] == 1 if a[i] is last occurred,
  //         0 otherwise
  fenwick_tree<int> x(n);
  unordered_map<int, int> lastpos;
  for (int j = 0; j < n; ++j) {
    if (lastpos.count(a[j])) 
      x.add(lastpos[a[j]], -1);
    lastpos[a[j]] = j;
    x.add(lastpos[a[j]], +1);
    for (auto q: queries[j]) 
      ans[q.k] = x.sum(q.j) - x.sum(q.i-1);
  }
  for (int i = 0; i < q; ++i)
    printf("%d\n", ans[i]);
}
