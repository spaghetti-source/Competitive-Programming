// SPOJ 13384: Nice Binary Trees
// http://www.spoj.cmm/problems/NICEBTRE/
//
// Solution: Parsing
//
// Knack of the string parsing:
// a parser returns a value and last+1 position.
// i.e., f(s) = (x,t) iff parse [s,t) == x

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)

#define fst first
#define snd second

pair<int,char*> solve(char *s) { // i からよむ
  if (s[0] == 'l') {
    return make_pair(0, s+1);
  } else {
    pair<int,char*> l = solve(s+1);
    pair<int,char*> r = solve(l.snd);
    r.fst = max(r.fst, l.fst) + 1;
    return r;
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    char s[20000];
    scanf("%s", s);   
    printf("%d\n", solve(s).fst);
  }
}
