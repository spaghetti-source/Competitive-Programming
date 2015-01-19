// SPOJ 5142: A Pair of Graphs
// http://www.spoj.com/problems/PAIRGRPH/
//
// Solution: ad-hoc
//
// 1-WA: forget 'undirected' thing.

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int f[10], adja[10][10], adjb[10][10];

int main() {
  int icase = 0;
  for (int n, ma, mb; scanf("%d %d %d", &n, &ma, &mb); ) {
    if (n == 0) break;
    printf("Case #%d: ", ++icase);
    int ia, ib, da, db;
    scanf("%d %d %d %d", &ia, &ib, &da, &db);
    memset(adja, 0, sizeof(adja));
    for (int i = 0; i < ma; ++i) {
      int u, v; 
      scanf("%d %d", &u, &v);
      adja[u][v] = adja[v][u] = 1;
    }
    memset(adjb, 0, sizeof(adjb));
    for (int i = 0; i < mb; ++i) {
      int u, v; 
      scanf("%d %d", &u, &v);
      adjb[u][v] = adjb[v][u] = 1;
    }
    iota(f, f+n, 0);
    int best = 1 << 30;
    do {
      int cost = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if        (adja[i][j] == 1 && adjb[f[i]][f[j]] == 0) {
            cost += min(da, ib);
          } else if (adja[i][j] == 0 && adjb[f[i]][f[j]] == 1) {
            cost += min(ia, db);
          }
        }
      }
      best = min(best, cost);
    } while (next_permutation(f, f+n));
    printf("%d\n", best/2);
  }
}
