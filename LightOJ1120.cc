// LightOJ 1120: Rectangle Union
// http://www.lightoj.com/volume_showproblem.php?problem=1120
//
// solution: coordinate compression + plane sweep with segment tree

#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

vector<int> C, A, ys;
void aux(int a, int b, int c, int l, int r, int k) {
  if ((a = max(a,l)) >= (b = min(b,r))) return;
  if (a == l && b == r) C[k] += c;
  else {
    aux(a, b, c, l, (l+r)/2, 2*k+1);
    aux(a, b, c, (l+r)/2, r, 2*k+2);
  }
  if (C[k]) A[k] = ys[r] - ys[l];
  else      A[k] = A[2*k+1] + A[2*k+2];
}

struct event { int l, h, c; }; // plane sweep
struct rectangle { int xl, yl, xh, yh; };
long long rectangle_area(vector<rectangle> rs) {
  ys.clear();
  /*
  vector<int> ys; // coordinate compression
  for (auto r: rs) 
    for (int y: {r.yl, r.yh})
      ys.push_back(y);
  */
  for (int i = 0; i < rs.size(); ++i) {
    ys.push_back(rs[i].yl);
    ys.push_back(rs[i].yh);
  }
  sort(all(ys)); ys.erase(unique(all(ys)), ys.end());

  int n = ys.size(); // measure tree

  /*
  vector<int> C(4*n), A(4*n);
  function<void (int,int,int,int,int,int)> aux = 
  [&](int a, int b, int c, int l, int r, int k) {
    if ((a = max(a,l)) >= (b = min(b,r))) return;
    if (a == l && b == r) C[k] += c;
    else {
      aux(a, b, c, l, (l+r)/2, 2*k+1);
      aux(a, b, c, (l+r)/2, r, 2*k+2);
    }
    if (C[k]) A[k] = ys[r] - ys[l];
    else      A[k] = A[2*k+1] + A[2*k+2];
  };
  */
  C = vector<int>(8*n); A = vector<int>(8*n);


  //struct event { int l, h, c; }; // plane sweep
  map<int, vector<event> > sweep;
  for (int i = 0; i < rs.size(); ++i) {
    rectangle &r = rs[i];
//  for (auto r: rs) {
    int l = distance(ys.begin(), lower_bound(all(ys), r.yl));
    int h = distance(ys.begin(), lower_bound(all(ys), r.yh));
    sweep[r.xl].push_back((event){l, h, +1});
    sweep[r.xh].push_back((event){l, h, -1});
  }

  long long area = 0;
  long long prev = -99999999;
  for (map<int,vector<event> >::iterator i = sweep.begin(); i != sweep.end(); ++i) {
    area += (i->fst - prev) * A[0];
    prev = i->fst;
    for (int j = 0; j < i->snd.size(); ++j) {
      event &e = i->snd[j];
      aux(e.l,e.h,e.c,0,n,0);
    }
  }

    /*
  for (auto &p: sweep) {
    area += (p.fst - prev) * A[0];
    prev = p.fst;
    for (auto &e: p.snd) 
      aux(e.l,e.h,e.c,0,n,0);
  }
  */
  return area;
}


int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int n; scanf("%d", &n);
    vector<rectangle> rs(n);
    for (int i = 0; i < n; ++i) 
      scanf("%d %d %d %d", &rs[i].xl, &rs[i].yl, &rs[i].xh, &rs[i].yh); 
    printf("Case %d: %lld\n", icase+1, rectangle_area(rs));
  }
}
