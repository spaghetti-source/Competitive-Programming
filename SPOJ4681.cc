// SPOJ 4681: Twice
// http://www.spoj.com/problems/TWICE/
//
// Solution: string (rolling hash), constant time optimization

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <set>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

typedef unsigned long long ULL;
const ULL p = 1000000009ULL;
int n;
char s[200010];
ULL pow[200010], phash[200010];
ULL H[200010];
void init() {
  pow[0] = 1; phash[0] = 0;
  REP(i, n) {
    phash[i+1] = s[i] + phash[i] * p;
    pow[i+1] = pow[i] * p;
  }
}
ULL rhash(int i, int j) {
  return phash[j] - phash[i] * pow[j-i];
}

bool check(int h) {
  for (int i = 0; i+h <= n; ++i) 
    H[i] = rhash(i, i+h);
  sort(H, H+n-h+1);
  for (int i = 0; i+1+h <= n; ++i)
    if (H[i] == H[i+1]) return true;
  return false;
}
int solve() {
  init();
  int l = 0, r = n;
  while (l+1 < r) {
    int m = (l+r)/2;
    if (check(m)) l = m;
    else          r = m;
  }
  return l;
}

int main() {
  gets(s);
  gets(s);
  n = strlen(s);
  printf("%d\n", solve());
}
