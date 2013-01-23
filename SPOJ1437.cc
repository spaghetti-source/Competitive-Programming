// SPOJ 1437: Longest path in a tree
//
// Solution: Graph
//
// Let f(u) be a farthest point of u.
// then, for any u, ( f(u), f(f(u)) ) is a farthest pair.
//
// prf. Let (x,y) be a farthest pair.
//
// x             v
//   \         /
//     - u --- 
//   /         \
// y              w
//
// Let f(u) = v, f(v) = w. (x,y) be a farthest pair.
// The four points inequality of tree is:
//   d(v,w) + d(x,y) <= d(x,v) + d(y,w)
// since w is farthest from v, 
//   d(x,v) <= d(v,w), d(y,w) <= d(v,w)
// therefore
//   d(x,y) <= d(v,w).
//
// Note: 4p-ineq hold iff tree.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define ALL(c) c.begin(), c.end()
#define REP(i,n) for(int i=0;i<n;++i)

using namespace std;

struct Graph {
  int n;
  vector< vector<int> > adj;
  Graph(int n) : n(n), adj(n) { }
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> dist;
  void visit(int u) {
    REP(i, adj[u].size()) {
      int v = adj[u][i];
      if (dist[v] > dist[u]+1) {
        dist[v] = dist[u] + 1;
        visit(v);
      }
    }
  }
  int diameter() { 
    dist.assign(n,n); dist[0] = 0; visit(0);
    int u = distance(dist.begin(), max_element(ALL(dist)));
    dist.assign(n,n); dist[u] = 0; visit(u);
    return *max_element(ALL(dist));
  }
};

int main() {
  int n; scanf("%d", &n);
  Graph G(n);
  for (int i = 0; i < n-1; ++i) {
    int u, v; scanf("%d %d", &u, &v);
    G.addEdge(u-1, v-1);
  }
  printf("%d\n", G.diameter());
}
