// SPOJ 243: Stable Marriage Problem
//
// Solution: T/O
//
// Gale-Shapley
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

typedef vector<int> VI;
typedef vector<VI> VVI;

VI stableMatching(VVI orderM, VVI orderW) {
  const int N = orderM.size();
  VVI preferW(N, VI(N+1, N));
  VI  matchW(N, N), proposedM(N);
  REP(w,N) REP(i,N) preferW[w][ orderW[w][i] ] = i;
  REP(n,N) for (int m = n; m < N; ) {
    int w = orderM[m][ proposedM[m]++ ];
    if (preferW[w][ m ] < preferW[w][ matchW[w] ])
      swap(m, matchW[w]);
  }
  return matchW;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    VVI orderW(n), orderM(n);
    int w, m; 
    REP(i, n) {
      scanf("%d", &w); --w;
      REP(j, n) {
        scanf("%d", &m); --m;
        orderW[w].push_back(m);
      }
    }
    REP(i, n) {
      scanf("%d", &m); --m;
      REP(j, n) {
        scanf("%d", &w); --w;
        orderM[m].push_back(w);
      }
    }
    VI matchW = stableMatching(orderM, orderW);
    REP(m, n) printf("%d %d\n", m+1, matchM[m]+1);
    

  }
}
