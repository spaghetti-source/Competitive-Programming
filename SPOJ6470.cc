// SPOJ 6470: Finding the Kth Prime
// http://www.spoj.com/problems/TDKPRIME/
//
// Solution: prime sieve / offline computing

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

// 18 lines; simple, and sufficient
int p[6000000] = {2}, ptop = 1;
const int NMAX = 100000010;
unsigned int _BV[NMAX/64];
#define _PRIME(n) !(_BV[n/64] & (1<<((n/2)&31)))
#define _COMPOSITE(n) (_BV[n/64] |= (1<<((n/2)&31)))
void sieve(int n) {
  unsigned int i, j;
  memset(_BV, 0, sizeof(_BV));
  for (i = 3; i*i < n; i+=2) 
    if (_PRIME(i)) {
      p[ptop++] = i;
      for (j = i*i; j < n; j += 2*i)
        _COMPOSITE(j);
    }
  for (; i < n; i+=2)
    if (_PRIME(i)) p[ptop++] = i;
}

int main() {
  sieve(100000000);
  int T; scanf("%d", &T);
  while (T--) {
    int k; scanf("%d", &k);
    printf("%d\n", p[k-1]);
  }
}
