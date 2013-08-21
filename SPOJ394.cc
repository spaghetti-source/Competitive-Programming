// SPOJ 394: Alphacode
// http://www.spoj.com/problems/ACODE/
//
// Solution: DP

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

typedef long long LL;
static LL c[10000];
LL solve(string s, int k) {
  if (k == s.size()) return 1;
  if (k == s.size()+1) return 0;
  if (s[k] == '0') return 0;
  if (c[k]) return c[k];
  LL res = solve(s, k+1);
  if (s[k] == '1' || (s[k] == '2' && s[k+1] <= '6')) res += solve(s, k+2);
  return c[k] = res;
}
int main() {
  string s;
  while (cin >> s, s != "0") {
    memset(c, 0, sizeof(c));
    cout << solve(s, 0) << endl;
  }
}

