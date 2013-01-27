// SPOJ 1479: The GbAaY Kingdom
//
// Solution: Minimum Diameter Spanning Tree
//
// Explicit tree construction is needed.
// It is a little hard.
//
//
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
  vector< vector<Weight> > A; // adj matrix

  Graph(int n) : n(n), A(n, vector<int>(n, INF)) {
    REP(u, n) A[u][u] = 0;
  }
  void addEdge(int s, int t, Weight w) {
    w *= 2; // because of half integrality
    if (w >= A[s][t]) return;
    A[s][t] = A[t][s] = w;
    edge.push_back(Edge(s, t, w));
  }



  vector<int> R; // radius
  vector<bool> visited;
  void traverse(int u, int sh = 0) { // explicit construction of sp-tree
    visited[u] = true;
    REP(v,n) if (R[v] == R[u] + A[u][v]) {
      if (!visited[v]) {
        printf("%d %d\n", u+1, v+1);
        traverse(v, sh+2);
      }
    }
  }
  vector< vector<Weight> > d;
  vector< vector<int> > L; 
  void farthestOrdering () {
    L.assign(n, vector<int>(n)); d = A;
    REP(z,n) REP(x,n) REP(y,n) 
      d[x][y] = min(d[x][y], d[x][z] + d[z][y]);
    REP(x,n) { 
      vector<PII> aux;
      REP(y,n) aux.push_back(PII(-d[x][y], y));
      sort(ALL(aux));
      REP(k,n) L[x][k] = aux[k].snd; // farthest ordering
    }
  }
  Weight minimumDiameterSpanningTree() {
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
    printf("%d\n", D); 
    R.resize(n); // explicit reconstruction by DFS
    REP(u, n) R[u] = min(d[e.s][u]+h, d[e.t][u]+e.w-h);
    visited.assign(n, false);
    if (h > 0) traverse(e.t);
    if (e.w > h) {
      traverse(e.s);
      if (h > 0) printf("%d %d\n", e.s+1, e.t+1);
    }
  }
};

int main () {
  int n, m; scanf("%d%d", &n, &m);
  Graph G(n);

  while (m--) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    G.addEdge(a, b, c);
  }
  G.minimumDiameterSpanningTree();
}
