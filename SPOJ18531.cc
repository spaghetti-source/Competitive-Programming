// SPOJ 18531: Barrelrider
// http://www.spoj.com/problems/BRLRIDER/
//
// Solution: geometry (tangent of circle)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <complex>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

// arg gives [-pi, pi] value.
double EPS = 1e-8;
int sign(double x) {
  if (x < -EPS) return -1;
  if (x > +EPS) return +1;
  return 0;
}

typedef complex<double> point;
struct circle { point p; double r; };

// Let q be a tangent point.
// The angle between q-p-c.p is 
//   sin(t) = r/|p - c.p|.
// and the solution is
//   p + (c.p - p) * exp(\pm it).
vector<point> tangent(point p, circle c) {
  double sin2 = c.r*c.r/norm(p - c.p);
  if (sign(1-sin2)  < 0) return {};
  if (sign(1-sin2) == 0) return {p};
  point z(sqrt(1-sin2), sqrt(sin2));
  return {p+(c.p-p)*conj(z), p+(c.p-p)*z};
}
const double PI = 4*atan(1.0);

// measure of union of x[j].
template <class T>
T covered_range(vector<pair<T, T>> x) {
  typedef pair<T, int> event;
  vector<event> es;
  for (int i = 0; i < x.size(); ++i) {
    es.push_back({x[i].fst, i});
    es.push_back({x[i].snd,~i});
  }
  sort(all(es));
  int c = 0;
  T a = es[0].fst, ans = 0;
  for (auto e: es) {
    if (c > 0) ans += e.fst - a;
    if (e.snd >= 0) ++c;
    else            --c;
    a = e.fst;
  }
  return ans;
}

void doit(int n) {
  vector<circle> cs;
  for (int i = 0; i < n; ++i) {
    double x, y, r;
    scanf("%lf %lf %lf", &x, &y, &r);
    cs.push_back({point(x,y), r});
  }
  point o(0,0);
  vector<pair<double ,double>> obstacles;
  for (int i = 0; i < n; ++i) {
    vector<point> ts = tangent(o, cs[i]);
    if (ts.size() == 0) {
      printf("100%\n");
      return;
    }
    if (ts.size() == 1) {
      point u = (cs[i].p - o) * point(0,-1);
      point v = (cs[i].p - o) * point(0,+1);
      ts = {u, v};
    }
    double a1 = arg(ts[0]);
    double a2 = arg(ts[1]);
    if (a1 >= a2) {
      obstacles.push_back({a1, PI});
      obstacles.push_back({-PI, a2});
    } else {
      obstacles.push_back({a1, a2});
    }
  }
  double cov = covered_range(obstacles);
  printf("%.0f%\n", 100.0 * cov / (2*PI));
}

int main() {
  int n; scanf("%d", &n); doit(n);
}
