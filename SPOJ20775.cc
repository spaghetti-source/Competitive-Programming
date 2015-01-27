// SPOJ 20775: Roger and tree
// http://www.spoj.com/problems/RTREE/
//
// Solution: dynamic programming (rooted-tree longest path)
//
// maintain 
//   1) longest path under u
//   2) longest half path (i.e., from u to some leaf)
// then the DP formula is obtained.

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdio>
#include <functional>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

struct edge {
  int src, dst;
};
struct tree {
  int n;
  vector<vector<edge>> adj;
  vector<int> half, full;
  tree(int n) : n(n), adj(n), half(n), full(n) { }
  void add_edge(int src, int dst) {
    adj[src].push_back({src, dst});
    adj[dst].push_back({dst, src});
  }

  void compute(int u, int p = -1) {
    bool no_child = true;
    for (auto e: adj[u]) {
      if (e.dst == p) continue;
      no_child = false;
      compute(e.dst, e.src);
    }
    if (no_child) {
      half[u] = full[u] = 0;
    } else {
      for (edge e: adj[u]) {
        int v = e.dst;
        if (v == p) continue;
        half[u] = max(half[u], 1 + half[v]);
        full[u] = max(full[u], full[v]);
      }
      full[u] = max(full[u], half[u]);

      int max1 = -1, max2 = -1;
      for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i].dst;
        if (v == p) continue;
        if      (half[v] > max1) { max2 = max1; max1 = half[v]; }
        else if (half[v] > max2) { max2 = half[v]; }
      }
      if (max1 >= 0 && max2 >= 0) 
        full[u] = max(full[u], 2 + max1 + max2);
    }
  }
};

int main() {
  int n; scanf("%d", &n);
  tree T(n);
  for (int i = 0; i < n-1; ++i) {
    int u, v; scanf("%d %d", &u, &v);
    T.add_edge(u-1, v-1);
  }
  int r; scanf("%d", &r);
  T.compute(r-1);

  int q; scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int u; scanf("%d", &u);
    printf("%d\n", T.full[u-1]);
  }
}
