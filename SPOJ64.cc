// SPOJ 64: Permutations
//
// Solution: DP
//
// f(n,k) length n, k inversion
// f(n,k) = sum f(m-1,k-l) 
//

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
LL f(int n, int k) {
  static LL c[100][100];
  if (k == 0) return 1;
  if (n == 1) return 0;
  if (c[n][k]) return c[n][k];

  LL s = 0;
  for (int j = 0; j <= min(n-1,k); ++j)
    s += f(n-1,k-j);
  return c[n][k] = s;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n, k; scanf("%d %d", &n, &k);
    printf("%lld\n", f(n,k));
  }
}
