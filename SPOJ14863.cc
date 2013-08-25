// SPOJ 14863: Summation of Multiples
// http://www.spoj.com/problems/SUM1/
//
// Solution: math (inclusion-exclusion)
//
// ans = sum of multiples of 3 + sum of multiples of 5 
//     - sum of multiples of 15
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

// sum of all multiples of k below n
LL f(LL n, LL k) {
  LL m = ((n-1) / k);
  return k*m*(m+1)/2;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    LL n; scanf("%lld", &n);
    printf("%lld\n", f(n,3) + f(n,5) - f(n,15));
  }
}
