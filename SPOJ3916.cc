// SPOJ 3916: Bicolor
// http://www.spoj.com/problems/BICOLOR/
//
// Solution: Graph (bipartiteness test)
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

struct Graph {
  int n;
  vector< vector<int> > adj;
  Graph(int n) : n(n), adj(n) { }
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> depth;
  bool visit(int u, int v) {
    FOR(w, adj[v]) {
      if (depth[*w] < 0) {
        depth[*w] = depth[v] + 1;
        if (!visit(v, *w)) return false;
      } else {
        if (*w != u && depth[*w] % 2 == depth[v] % 2) 
          return false;
      }
    }
    return true;
  }
  bool isBipartite() {
    depth.assign(n, -1);
    REP(u, n) {
      if (depth[u] < 0) {
        depth[u] = 0;
        if (!visit(-1, u)) return false;
      }
    }
    return true;
  }
};

int main() {
  int n, m;
  while (scanf("%d %d", &n, &m) == 2 && n != 0) {
    Graph G(n);
    REP(i,m) {
      int u, v; scanf("%d %d", &u, &v);
      G.addEdge(u, v);
    }
    if (G.isBipartite()) printf("BICOLORABLE\n");
    else printf("NOT BICOLORABLE\n");
  }
}
