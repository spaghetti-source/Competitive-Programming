// SPOJ 401: Translations
// http://www.spoj.com/problems/TRANSL/
//
// Solution: graph isomorphism

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstring>
#include <unordered_set>
#include <functional>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

struct graph {
  int n;
  vector<unordered_set<int>> adj, rdj;
  graph(int n) : n(n), adj(n), rdj(n) { } 
  void add_edge(int src, int dst) {
    adj[src].insert(dst);
    rdj[dst].insert(src);
  }
};

vector<int> isomorphic(graph G, graph H) {
  if (G.n != H.n) return {};
  int n = G.n;
  vector<int> GtoH(n, -1), HtoG(n, -1); 
  vector<int> inG(n), outG(n), inH(n), outH(n); 

  function<bool (int)> match = [&](int k) {
    if (k == n) return true;

    int s = -1; // large degree heuristics
    for (int t = 0; t < n; ++t) {
      if (GtoH[t] >= 0) continue;
      if (s == -1 || inG[s] + outG[s] < inG[t] + outG[t]) s = t;
    }
    for (int u = 0; u < n; ++u) {
      auto check = [&](int s, int u) { // VF2 feasibility function
        if (HtoG[u] >= 0) return false;
        if (inG[s] != inH[u]) return false;
        if (outG[s] != outH[u]) return false;
        int TinG = 0, ToutG = 0, TnewG = 0, TinH = 0, ToutH = 0, TnewH = 0;
        for (int t: G.adj[s]) {
          if (GtoH[t] >= 0) { 
            if (!H.adj[u].count(GtoH[t])) return false;
          } else {
            if (inG[t]) ++TinG;
            if (outG[t]) ++ToutG;
            if (!inG[t] && !outG[t]) ++TnewG;
          }
        }
        for (int v: H.adj[u]) {
          if (HtoG[v] >= 0) {
            if (!G.adj[s].count(HtoG[v])) return false;
          } else {
            if (inH[v]) ++TinH;
            if (outH[v]) ++ToutH;
            if (!inH[v] && !outH[v]) ++TnewH;
          }
        }
        if (TinG != TinH || ToutG != ToutH || TnewG != TnewH) return false;
        for (int t: G.rdj[s]) {
          if (GtoH[t] >= 0) {
            if (!H.rdj[u].count(GtoH[t])) return false;
          } else {
            if (inG[t]) ++TinG;
            if (outG[t]) ++ToutG;
            if (!inG[t] && !outG[t]) ++TnewG;
          }
        }
        for (int v: H.rdj[u]) {
          if (HtoG[v] >= 0) {
            if (!G.rdj[s].count(HtoG[v])) return false;
          } else {
            if (inH[v]) ++TinH;
            if (outH[v]) ++ToutH;
            if (!inH[v] && !outH[v]) ++TnewH;
          }
        }
        if (TinG != TinH || ToutG != ToutH || TnewG != TnewH) return false;
        return true;
      };
      if (!check(s, u)) continue;
      ++inG[s]; ++outG[s];
      for (int t: G.rdj[s]) ++inG[t];
      for (int t: G.adj[s]) ++outG[t];
      ++inH[u]; ++outH[u];
      for (int v: H.rdj[u]) ++inH[v];
      for (int v: H.adj[u]) ++outH[v];

      GtoH[s] = u; HtoG[u] = s;
      if (match(k+1)) return true;
      GtoH[s] = -1; HtoG[u] = -1;

      --inG[s]; --outG[s];
      for (int t: G.rdj[s]) --inG[t];
      for (int t: G.adj[s]) --outG[t];
      --inH[u]; --outH[u];
      for (int v: H.rdj[u]) --inH[v];
      for (int v: H.adj[u]) --outH[v];
    }
    return false;
  };
  match(0);
  return GtoH;
}

#include <map>
template <class T>
struct dictionary {
  std::map<T, size_t> dict;
  std::vector<T> idict;
  size_t id(T s) { 
    if (!dict.count(s)) {
      dict[s] = idict.size();
      idict.push_back(s);
    }
    return dict[s];
  }
  T value(size_t id) {
    return idict[id];
  }
  size_t size() const {
    return dict.size();
  }
};

int main() {
  for (int icase = 0; ; ++icase) {
    int m; scanf("%d", &m);
    if (m == 0) break;
    if (icase > 0) printf("\n");

    dictionary<string> dic1, dic2;
    vector<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
      char s[1024], t[1024];
      scanf("%s %s", s, t);
      edges.push_back({dic1.id(s), dic1.id(t)});
    }
    graph g(dic1.size());
    for (auto e: edges)
      g.add_edge(e.fst, e.snd);

    edges.clear();
    for (int i = 0; i < m; ++i) {
      char s[1024], t[1024];
      scanf("%s %s", s, t);
      edges.push_back({dic2.id(s), dic2.id(t)});
    }
    graph h(dic2.size());
    for (auto e: edges)
      h.add_edge(e.fst, e.snd);

    vector<int> corr = isomorphic(g, h);
    for (auto p: dic1.dict) {
      cout << p.fst << "/" << dic2.value(corr[p.snd]) << endl;
    }
  }
}
