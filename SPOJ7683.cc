// SPOJ 7683: Powered and Squared
// http://www.spoj.com/problems/CSQUARE/
//
// Solution: math (modulo)
//
// a^b[0,k) = a^( 3 * b[0,k-1) ) * a^b[k]
//          = ( a^b[0,k-1) )^3 * a^b[k]

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
LL solve(LL a, char b[], LL M) {
  int n = strlen(b);
  LL c[3];
  c[0] = 1; c[1] = a%M; c[2] = (a*a)%M;
  LL f[n+1];
  f[0] = 1;
  for (int i = 0; i < n; ++i) 
    f[i+1] = (((((f[i]*f[i])%M)*f[i])%M) * c[b[i]-'0'])%M;
  return f[n];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    LL a, M;
    char b[256];
    scanf("%lld %s %lld", &a, b, &M);
    printf("%lld\n", solve(a, b, M));
  }
}
