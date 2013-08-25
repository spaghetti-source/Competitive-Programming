// SPOJ 15560: Help the old King
// http://www.spoj.com/problems/IITKWPCG/
//
// Solution: minimum spanning tree

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

typedef long long LL;

struct Edge {
  int src, dst, weight;
  Edge(int src, int dst, int weight) :
    src(src), dst(dst), weight(weight) { }
};
bool operator < (Edge e, Edge f) {
  return e.weight > f.weight;
}

struct Graph {
  int n;
  vector< vector<Edge> > adj;
  Graph(int n) : n(n), adj(n) { }
  void addEdge(int u, int v, int w) {
    adj[u].push_back( Edge(u, v, w) );
    adj[v].push_back( Edge(v, u, w) );
  }
  int minimumSpanningTree() {
    int cost = 0;
    vector<int> connected(n);
    priority_queue<Edge> Q;
    Q.push(Edge(-1, 0, 0));
    while (!Q.empty()) {
      int u = Q.top().dst;
      int w = Q.top().weight;
      Q.pop();
      if (connected[u]++) continue;
      cost += w;
      FOR(e, adj[u]) Q.push(*e);
    }
    return cost;
  }
};

void doit() {
  int n, m;
  scanf("%d %d", &n, &m);
  Graph G(n);
  REP(i, m) {
    int u, v;
    LL c;
    scanf("%d %d %lld", &u, &v, &c);
    int e = 0;
    while (c > 1) {
      c /= 2;
      ++e;
    }
    G.addEdge(u-1, v-1, e); 
  }
  printf("%d\n", G.minimumSpanningTree()+1);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) doit();
}
