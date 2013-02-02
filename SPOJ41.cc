// SPOJ 41: Play on Words 
//
// Solution: euler path

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
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
  struct Edge {
    int s, t;
    Edge(int s, int t) : s(s), t(t) { }
  };
  vector< vector<Edge> > adj;
  Graph(int n) : n(n), adj(n) { }
  void addEdge(int u, int v) {
    adj[u].push_back( Edge(u,v) );
  }

  vector<int> path;
  int visit(int s) {
    while (!adj[s].empty()) {
      int t = adj[s].back().t;
      adj[s].pop_back();
      visit(t); 
    }
    path.push_back(s);
  }
  bool hasEulerPath(int s = -1) {
    vector< vector<Edge > > tmp = adj; // backup
    int m = 0;
    vector<int> deg(n);
    REP(u,n) {
      FOR(e, adj[u]) --deg[e->t];
      deg[u] += adj[u].size();
      m += adj[u].size();
    }
    int k = n - count(ALL(deg), 0);
    if (k == 0) s = 0;
    else if (k == 2) 
      REP(u, n) if (deg[u] == 1) s = u;
    if (s == -1) return false;
    path.clear(); visit(s);
    // adj = tmp;
    return path.size() == m + 1;
  }
};

char buf[10000]; 
int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int m; scanf("%d", &m);
    int n = 0;
    map<char, int> M;
    vector<string> s;
    for (int i = 0; i < m; ++i) {
      scanf("%s", buf); s.push_back(string(buf));
      int a = s[i][0], b = s[i][s[i].size()-1];
      if (!M.count(a)) M[a] = n++;
      if (!M.count(b)) M[b] = n++;
    }
    Graph G(n);
    for (int i = 0; i < m; ++i) {
      int a = s[i][0], b = s[i][s[i].size()-1];
      G.addEdge( M[a], M[b] );
    }
		if (G.hasEulerPath()) printf("Ordering is possible.\n");
		else printf("The door cannot be opened.\n");
  }
}
