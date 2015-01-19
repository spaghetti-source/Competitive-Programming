// SPOJ 21061: Yet Another Subset Sum Problem
// http://www.spoj.com/problems/YASSP/
//
// Solution: dynamic programming

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int x[50+10];
long long G[1000*50+10];
int F[1000*50+10];

void doit() {
  int n; scanf("%d", &n);
  int M = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &x[i]);
    M += x[i];
  }
  memset(G, 0, sizeof(G));
  G[0] = 1; 
  for (int i = 0; i < n; ++i) 
    for (int m = M-x[i]; m >= 0; --m) 
      G[m+x[i]] |= (G[m] << 1);

  /*
  // check
  for (int m = 0; m <= M; ++m) {
    int a = G[m];
    printf("%d: ", m);
    for (int i = 0; i <= n; ++i)
      printf("%d", !!(a & (1<<i)));
    printf("\n");
  }
  */
  int maxm = M;
  memset(F, 0, sizeof(F));
  for (int m = M; m >= 1; --m) {
    for (int i = 0; i <= n; ++i)
      F[m] += !!(G[m] & (1ull<<i));
    if (F[m] >= F[maxm]) maxm = m;
  }
  printf("%d %d\n", F[maxm], maxm);
}
int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) doit();
}
