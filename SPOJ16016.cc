// SPOJ 16016. Queue (Pro)
// http://www.spoj.com/problems/QUE2/
//
// Solution: sqrt array

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

template <class T>
struct sqrt_array {
  int n, m;
  vector<vector<T>> x;
  sqrt_array(int n) : n(n), m(sqrt(n)) {
    x.assign(1+m, vector<T>(n/m));
  }
  pair<int,int> id(int k) {
    for (int i = 0; k >= 0; k -= x[i++].size()) 
      if (k < x[i].size()) return {i, k};
  }
  void erase(int k) {
    --n;
    auto p = id(k);
    x[p.fst].erase(x[p.fst].begin() + p.snd);
    if (x[p.fst].size() == 0) x.erase(x.begin() + p.fst);
  }
  T &operator[](int k) {
    auto p = id(k);
    return x[p.fst][p.snd];
  }
  const int size() const { return n; }
};

void doit() {
  int n; scanf("%d", &n);
  vector<pair<int, int>> H(n);
  for (int i = 0; i < n; ++i) 
    scanf("%d", &H[i].fst);
  for (int i = 0; i < n; ++i) 
    scanf("%d", &H[i].snd);
  sort(all(H));

  vector<int> ans(n);
  sqrt_array<int> L(n);
  for (int i = 0; i < n; ++i) L[i] = i;
  for (auto h: H) {
    int k = L[h.snd];
    ans[k] = h.fst;
    L.erase(h.snd);
  }
  for (int i = 0; i < n; ++i) {
    if (i > 0) printf(" ");
    printf("%d", ans[i]);
  }
  printf("\n");
}
int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase ; ++icase) doit();
}
