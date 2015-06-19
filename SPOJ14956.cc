// SPOJ 14956: Submerging Island
// http://www.spoj.com/problems/SUBMERGE/
//
// solution: articulation points

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <unordered_set>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

struct graph {
  int n;
  vector<vector<int>> adj;
  graph(int n) : n(n), adj(n) { }
  void add_edge(int src, int dst) {
    adj[src].push_back(dst);
    adj[dst].push_back(src);
  }
};

void biconnected_components(graph g) {
  vector<int> arts(g.n), num(g.n), low(g.n);
  vector<pair<int,int>> S;
  vector<unordered_set<int>> comps;
  function<void(int,int,int&)> dfs = [&](int p, int i, int &t) { // p -> i
    num[i] = low[i] = ++t; 
    for (int j: g.adj[i]) {
      if (j == p) continue;
      S.push_back({i, j});
      if (num[j] == 0) {
        dfs(i, j, t);
        low[i] = min(low[i], low[j]);
        if (num[i] <= low[j]) {
          if (num[i] != 1 || low[j] > 2) arts[i] = true;
          comps.push_back(unordered_set<int>());
          while (1) {
            int u = S.back().fst, v = S.back().snd;
            S.pop_back();
            comps.back().insert(u); 
            comps.back().insert(v);
            if (u == i && v == j) break;
          }
        }
      } else low[i] = min(low[i], num[j]);
    }
  };
  int t;
  for (int i = 0; i < g.n; ++i)
    if (num[i] == 0) dfs(-1, i, t = 0);

  // SPOJ SUBMERGE
  int count = 0;
  for (int i = 0; i < g.n; ++i) 
    count += arts[i];
  printf("%d\n", count);
}

int main() {
  for (int n, m; ~scanf("%d %d", &n, &m) && n; ) {
    graph g(n);
    for (int i = 0; i < m; ++i) {
      int u, v; scanf("%d %d", &u, &v);
      g.add_edge(u-1, v-1);
    }
    biconnected_components(g);
  }
}
