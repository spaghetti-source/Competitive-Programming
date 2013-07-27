// SPOJ 12: The Game of Master-Mind
// http://www.spoj.com/problems/MMIND/
// 
// Solution: exhaustive search
// (Note: Mastermind is NP-hard)

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cmath>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

int P, C, M;

struct Query {
  int guess[105];
  int count[105];
  int hit, match;
} query[105];
int solution[105];

bool solve(int p) {
  REP(m, M) 
    if (query[m].hit < 0   || query[m].hit   > P-p ||
        query[m].match < 0 || query[m].match > P-p) return false;
  if (p == P) return true;
  REP(c, C) {
    solution[p] = c;
    REP(m, M) {
      if (query[m].guess[p] == c)  --query[m].hit;
      if (query[m].count[c]-- > 0) --query[m].match;
    }
    if (solve(p+1)) return true;
    REP(m, M) {
      if (query[m].guess[p] == c)  ++query[m].hit;
      if (++query[m].count[c] > 0) ++query[m].match;
    }
  }
  return false;
}

void doit() {
  memset(query, 0, sizeof(query));
  scanf("%d %d %d", &P, &C, &M);
  REP(m, M) {
    REP(p, P) { 
      int g; scanf("%d", &g);
      query[m].guess[p] = g-1;
      ++query[m].count[g-1];
    }
    scanf("%d %d", &query[m].hit, &query[m].match);
    query[m].match += query[m].hit;
  }
  if (solve(0)) {
    REP(p, P) {
      if (p > 0) printf(" ");
      printf("%d", solution[p]+1);
    }
    printf("\n");
  } else {
    printf("You are cheating!\n");
  }
}

int main() { 
  int T;
  scanf("%d", &T);
  while (T--) doit();
}
