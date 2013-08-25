// SPOJ 9952: 111...1 Squared
// http://www.spoj.com/problems/GUANGGUN/
//
// Solution: math
//
// see http://oeis.org/A080151
//
// 81*(Floor[n/9] + FractionalPart[n/9]^2)
//
// 2nd term = (n - 9*[n/9])^2
//

#include <iostream>
#include <cstdio>
#include <cmath>
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

LL solve(LL n) {
  LL a = 81 * (n/9);
  LL b = (n - 9*(n/9)); b *= b;
  return a + b;
}

const LL M = 1000000007;
int main() {
  for (LL n; scanf("%lld", &n) == 1; ) {
    printf("%lld\n", solve(n));
  }
}
