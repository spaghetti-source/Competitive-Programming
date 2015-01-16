// SPOJ 3377: A Bug’s Life
// http://www.spoj.com/problems/BUGLIFE/
//
// Solution: bipartiteness
//
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

using namespace std;

struct edge { int src, dst; };
struct graph {
  int n;
  vector<vector<edge> > adj;
  graph(int n = 0) : n(n), adj(n) { }
  void add_edge(int src, int dst) {
    n = max(n, max(src, dst)+1);
    adj.resize(n);
    adj[src].push_back((edge){src, dst});
    adj[dst].push_back((edge){dst, src});
  }

  vector<int> color;

  bool dfs(int i, int c) {
    color[i] = c;
    for (auto e: adj[i]) {
      if (color[e.dst] ==  c) return false;
      if (color[e.dst] == -1 && !dfs(e.dst, !c)) return false;
    }
    return true;
  }
  bool is_bipartite() {
    color.assign(n, -1);
    for (int i = 0; i < n; ++i) 
      if (color[i] == -1) 
        if (!dfs(i, 0)) return false;
    return true;
  }
};


int main() {
  int ncase;
  scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    printf("Scenario #%d:\n", icase+1);
    int n, m;
    scanf("%d %d", &n, &m);
    graph g(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d %d", &u, &v);
      g.add_edge(u-1, v-1);
    }
    if (g.is_bipartite()) printf("No suspicious bugs found!\n");
    else                  printf("Suspicious bugs found!\n");
  }
}
