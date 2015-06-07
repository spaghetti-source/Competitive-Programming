// SPOJ 1247: Monster Trap
// http://www.spoj.com/problems/MONSTER/
//
// Solution: 2D geometry (planar graph construction)

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <complex>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef complex<double> point;
namespace std {
bool operator < (point p, point q) {
  if (real(p) != real(q)) return real(p) < real(q);
  return imag(p) < imag(q);
}
};
istream &operator>>(istream &is, point &p) {
  double x, y;
  is >> x >> y;
  p = point(x, y);
  return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &x) {
  for (auto &a: x) os << a << " ";
  return os;
}

double dot(point p, point q)   { return real(conj(p) * q); }
double cross(point p, point q) { return imag(conj(p) * q); }
double EPS = 1e-8;
int sign(double x) {
  if (x < -EPS) return -1;
  if (x > +EPS) return +1;
  return 0;
}
struct segment { point p, q; segment(point a, point b) : p(a), q(b) {} };
vector<point> intersect(segment S, segment T) {
  double a = cross(S.q - S.p, T.q - T.p);
  double b = cross(T.p - S.p, T.q - T.p); 
  double c = cross(S.q - S.p, S.p - T.p);
  if (a < 0) { a *= -1; b *= -1; c *= -1; }
  if (sign(b) < 0 || sign(a-b) < 0 ||
      sign(c) < 0 || sign(a-c) < 0) return {};      // disjoint
  if (sign(a) != 0) return {S.p + (S.q - S.p)*b/a}; // properly crossing
  if (sign(a) == 0) {                               // same line
    vector<point> ps;
    if (sign(dot(S.p - T.p, S.q - T.p)) <= 0) ps.push_back(T.p);
    if (sign(dot(S.p - T.q, S.q - T.q)) <= 0) ps.push_back(T.q);
    if (sign(dot(T.p - S.p, T.q - S.p)) <  0) ps.push_back(S.p);
    if (sign(dot(T.p - S.q, T.q - S.q)) <  0) ps.push_back(S.q);
    return ps;
  }
  return {};
}

// doubly linked edge list
struct planar_graph {
  vector<point> ps;           // V -> Point
  vector<int> incident;       // V -> E
  vector<int> src, dst, next; // E -> E

  typedef long long ll;
  unordered_map<ll, vector<int>> vhash;
  int add_vertex(point p) {
    ll h = ((ll)(real(p)*1000)) << 32 | (ll)(imag(p)*1000);
    for (auto i: vhash[h]) 
      if (sign(abs(ps[i] - p)) == 0) return i;
    vhash[h].push_back(ps.size());
    ps.push_back(p);
    incident.push_back(-1);
    return vhash[h].back();
  }
  int add_edge(int i, int j) {
    auto add_half = [&](int i, int j) {
      int e = src.size();
      src.push_back(i); 
      dst.push_back(j);
      next.push_back(e);
      if (incident[i] < 0) incident[i] = e;
      int t = incident[i];
      if (next[t] != t) {
        while (1) {
          int s = next[t];
          if (sign(cross(ps[dst[t]]-ps[i], ps[j]-ps[i])) <= 0 &&
              sign(cross(ps[dst[s]]-ps[i], ps[j]-ps[i])) >= 0) break;
          t = s;
        }
      }
      swap(next[e], next[t]);
      return e;
    };
    return add_half(j, i), add_half(i, j); // e^1 is the reversed edge of e
  }

  int traverse(point p) { // it returns true if some cycle contains point p 
    vector<int> visited(src.size());
    for (int e = 0; e < src.size(); ++e) {
      if (visited[e]) continue;
      int in = false, t = e;
      do {
        visited[t] = 1;
        point a = ps[src[t]] - p, b = ps[dst[t]] - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b))
          if (cross(a, b) < 0) in = !in;
        if (sign(cross(a, b)) == 0 && dot(a, b) <= 0) return true;
        t = next[t^1];
      } while (e != t);
      if (in) return true;
    }
    return false;
  }
};

planar_graph segment_arrangement(vector<segment> segs) {
  planar_graph g;
  vector<vector<int>> on(segs.size());
  for (int i = 0; i < segs.size(); ++i) {
    on[i].push_back( g.add_vertex(segs[i].p) );
    on[i].push_back( g.add_vertex(segs[i].q) );
    for (int j = i+1; j < segs.size(); ++j) {
      vector<point> is = intersect(segs[i], segs[j]);
      for (auto q: is) {
        on[i].push_back( g.add_vertex(q) );
        on[j].push_back( g.add_vertex(q) );
      }
    }
  }
  for (int i = 0; i < on.size(); ++i) {
    sort(all(on[i]), [&](int u, int v) { return g.ps[u] < g.ps[v]; });
    for (int j = 0; j+1 < on[i].size(); ++j) 
      if (on[i][j] != on[i][j+1]) 
        g.add_edge(on[i][j], on[i][j+1]);
  }
  return g;
}


int main() {
  for (int m; cin >> m && m > 0; ) {
    vector<segment> segs;
    for (int i = 0; i < m; ++i) {
      point p, q;
      cin >> p >> q;
      segs.push_back({p, q});
    }
    auto g = segment_arrangement(segs);
    if (g.traverse(point(0.0, 0.0))) cout << "yes" << endl;
    else                             cout << "no" << endl;
  }
}
