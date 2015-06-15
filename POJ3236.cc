// POJ 3236: Michelle's Evaluation
// http://poj.org/problem?id=3236
//
// Solution: cograph recognition
//
#include <iostream>
#include <vector>
#include <list>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>
#include <set>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

struct graph {
  int n;
  vector<vector<int> > adj;
  graph(int n) : n(n), adj(n) { }
  void add_edge(int src, int dst) {
    adj[src].push_back(dst);
    adj[dst].push_back(src);
  }
};

// brute-force cograph verification
bool is_cograph_n(graph g, bool first = true) { 
  if (g.n <= 3) return true;
  for (int i = 0; i < g.adj.size(); ++i)
    sort(all(g.adj[i]));
  vector<int> index(g.n, -1);
  for (int i = 0; i < g.n; ++i) {
    if (index[i] >= 0) continue;
    int size = 0;
    index[i] = size++;
    vector<int> S(1,i), comps;
    while (!S.empty()) {
      int j = S.back(); S.pop_back();
      comps.push_back(j);
      for (int p = 0; p < g.adj[j].size(); ++p) {
        int k = g.adj[j][p];
        if (index[k] < 0) {
          index[k] = size++;
          S.push_back(k);
        }
      }
    }
    graph h(size);
    for (int j = 0; j < comps.size(); ++j) 
      for (int k = j+1; k < comps.size(); ++k) 
        if (!binary_search(all(g.adj[comps[j]]), comps[k]))
          h.add_edge(index[comps[j]], index[comps[k]]);
    if (!first && g.n == h.n) return false;    // both G and G' are connected 
    if (!is_cograph_n(h, false)) return false; // some component is not a cograph
  }
  return true;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  graph g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    g.add_edge(u-1, v-1);
  }
  printf("%s\n", (is_cograph_n(g) ? "Yes" : "No"));
}
