// SPOJ 22529: Dandiya Night and Violence
// http://www.spoj.com/problems/DANDVIOL/
//
// Solution: union find

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())


struct union_find {
  vector<int> p; 
  union_find(int n) : p(n, -1) { };
  bool unite(int u, int v) { 
    if ((u = root(u)) == (v = root(v))) return false;
    if (p[u] > p[v]) swap(u, v);
    p[u] += p[v]; p[v] = u;
    return true;
  }
  bool find(int u, int v) { return root(u) == root(v); }
  int root(int u) { return p[u] < 0 ? u : p[u] = root(p[u]); }
  int size(int u) { return -p[root(u)]; }
};

int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int m, f;
    scanf("%d %d", &m, &f);
    vector<pair<int,int>> edges;
    for (int i = 0; i < m; ++i) {
      int u, v; scanf("%d %d", &u, &v); --u; --v;
      edges.push_back({u, v});
    }
    int n = 2 * m;
    union_find uf(n);
    for (int i = 0; i < f; ++i) {
      int u, v; scanf("%d %d", &u, &v); --u; --v;
      uf.unite(u, v);
    }
    for (int i = 0; i < m; ++i) {
      edges[i].fst = uf.root(edges[i].fst);
      edges[i].snd = uf.root(edges[i].snd);
      if (edges[i].fst > edges[i].snd)
        swap(edges[i].fst, edges[i].snd);
    }
    sort(all(edges));
    edges.erase(unique(all(edges)), edges.end());

    int ans = 0;
    for (auto e: edges) {
      if (e.fst == e.snd) continue;
      ans += uf.size(e.fst) * uf.size(e.snd);
    }
    printf("%d\n", ans);
  }
}
