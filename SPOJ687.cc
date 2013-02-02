// SPOJ 687: Repeats
// http://www.spoj.com/problems/REPEATS/
//
// Solution: String (LCP)
//
// A bit slow, because O(log n) LCP computation.
// Using a suffix arary, O(1) LCP is possible.

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

typedef unsigned long long ULL;
struct RollingHash {
  static const ULL p = 1000000007ULL;
  string s;
  int n;
  vector<ULL> pow, phash;
  RollingHash(string s) : s(s), n(s.size()),
    pow(n+1,1), phash(n+1,0) {
    REP(i, n) {
      phash[i+1] = s[i] + phash[i] * p;
      pow[i+1] = pow[i] * p;
    }
  }
  ULL hash(int i, int j) { // hash of s[i,j) 
    return phash[j] - phash[i] * pow[j-i];
  }
  int lcp(int i, int j) { 
    int l = 0, r = min(n-i, n-j)+1;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (hash(i,i+m) == hash(j,j+m)) l = m;
      else                            r = m;
    }
    return l;
  }
};
int solve(string s) {
  int n = s.size();
  RollingHash R(s);
  int opt = 0;
  for (int w = 1; w <= n/2; ++w) {
    for (int i = 0; i+w < n; i+=w) {
      int ell = R.lcp(i, i+w);
      if (ell) {
        int res = ell / w;
        int j = i - (w - ell % w);
        if (j >= 0 && R.lcp(j, j+w) >= w) ++res;
        opt = max(opt, res);
      }
    }
  }
  return opt + 1;
}
char buf[50010];
int main() {
  int T; scanf("%d\n", &T);
  while (T--) {
    int n; scanf("%d\n", &n);
    memset(buf, 0, sizeof(buf));
    for (int i = 0; i < n; ++i)
      scanf("%c\n", &buf[i]);
    string s(buf);
    printf("%d\n", solve(s));
  }
}
