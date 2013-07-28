// SPOJ 15310: Peter Quest
// http://www.spoj.com/problems/VPL2_BC/
//
// Solution: ad-hoc (sparse table)

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

int dx[] = {1,1,0,-1,-1,-1,0,1}, 
    dy[] = {0,1,1,1,0,-1,-1,-1};

void doit() {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  typedef pair<int,int> Entry;
  vector< vector<Entry> > rows(n);
  while (k--) {
    int x, y; 
    scanf("%d %d", &y, &x);
    rows[y].push_back(Entry(x, 9));
    for (int i = 0; i < 8; ++i) 
      if (y+dy[i] >= 0 && y+dy[i] < n &&
          x+dx[i] >= 0 && x+dx[i] < m)
        rows[y+dy[i]].push_back(Entry(x+dx[i], 1));
  }
  REP(k, n) {
    vector<int> row(m);
    FOR(e, rows[k]) row[e->fst] += e->snd;
    REP(i, m) 
      if      (row[i] == 0) putchar('-');
      else if (row[i] <= 8) putchar('0'+row[i]);
      else                  putchar('*');
    putchar('\n');
  }
}

int main() { 
  int T; scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    printf("Scenario #%d:\n", t);
    doit();
  }
}
