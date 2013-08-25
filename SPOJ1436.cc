// SPOJ 1436: Is it a tree
// http://www.spoj.com/problems/PT07Y/
//
// Solution: graph
//
// T is tree iff T is connected and does not have a cycle

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
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
  vector<int> prev;
  int dfs(int u) {
    int count = 0;
    FOR(v, adj[u]) {
      if (prev[u] == *v) continue;
      if (prev[*v] >= 0) return -2*n;
      prev[*v] = u;
      int c = dfs(*v);
      if (c < 0) return c;
      count += c;
    }
    return count + 1;
  }
  bool isTree() {
    prev.assign(n, -1);
    return dfs(0) == n;
  }
};
int main() {
  int n, m; 
  scanf("%d %d", &n, &m);
  Graph G(n);
  REP(i, m) {
    int u, v;
    scanf("%d %d", &u, &v);
    G.addEdge(u-1,v-1);
  }
  printf("%s\n", G.isTree() ? "YES" : "NO");
}
