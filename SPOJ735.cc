// SPOJ 735 Minimum Diameter Spanning Tree
//
// Solution: T/O.
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

typedef pair<int, int> PII;
typedef int Weight;
const Weight INF = 1 << 28;
struct Graph {
  struct Edge {
    int s, t;
    Weight w;
    Edge(int s, int t, Weight w) : s(s), t(t), w(w) { }
  };
  int n;
  vector<Edge> edge; // edge list
  vector< vector<int> > adj; // adj list

  Graph(int n) : n(n), adj(n) { }
  void addEdge(int s, int t, Weight w) {
    w *= 2; // because of half integrality
    edge.push_back(Edge(s, t, w));
    adj[s].push_back(t);
    adj[t].push_back(s);
  }


  vector< vector<Weight> > d;
  vector< vector<int> > L; 
  void farthestOrdering () {
    L.assign(n, vector<int>()); 
    d.assign(n, vector<int>(n, INF));
    REP(s, n) {
      d[s][s] = 0;
      queue<int> Q; Q.push(s);
      while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        L[s].push_back(u); 
        REP(i, adj[u].size()) {
          int v = adj[u][i];
          if (d[s][v] > d[s][u] + 2) { // half integrality
            d[s][v] = d[s][u] + 2;
            Q.push(v);
          }
        }
      }
      reverse(ALL(L[s]));
    }
  }
  Weight minimumDiameterSpanningTree() {
    if (n <= 1) return 0;
    farthestOrdering(); // preprocessing
    int h, D = INF;
    Edge &e = edge[0];
    FOR(it, edge) {
      int s = it->s, t = it->t; // for simplicity
      Weight w = it->w;
      if (d[s][L[t][0]] + d[t][L[s][0]] + w > 2*D) continue; // Halpern bound
      if (L[s][0] == L[t][0]) continue; // no-coincide condition

      vector<PII> a;
      for (int i = n-1; i >= 0; --i) {
        pair<int,int> p = make_pair(d[s][L[s][i]], d[t][L[s][i]]);
        while (!a.empty() && a.back().snd <= p.snd) a.pop_back();
        a.push_back(p);
      }
      reverse(ALL(a));

      int x = 0, y = a[0].fst; 
      if (a[t].snd < y) { x = w; y = a.back().snd; }
      REP(i, a.size()-1) {
        int ay = (a[i].snd + a[i+1].fst + w)/2;
        if (ay < y) { y = ay; x = ay - a[i+1].fst; }
      }
      int De = 0;
      REP(i, n) De = max(De, min(d[s][i]+x, d[t][i]+w-x));
      if (De < D) { D = De; h = x; e = *it; }
    }
    return D;
  }
};

int main () {
  int T; scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    Graph G(n);
    for (int i = 0; i < n; ++i) {
      int u, m; scanf("%d %d", &u, &m);
      for (int j = 0; j < m; ++j) {
        int v; scanf("%d", &v);
        G.addEdge(u-1, v-1, 1);
      }
    }
    printf("%d\n", G.minimumDiameterSpanningTree());
  }
}
