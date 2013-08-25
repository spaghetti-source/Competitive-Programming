// SPOJ 6470: Finding the Kth Prime
// http://www.spoj.com/problems/TDKPRIME/
//
// Solution: prime sieve

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

vector<int> primeList(int n) {
  const int M = 1 << 14, SQR = 1 << 16;
  static bool buf[M], Q[SQR];
  // primality table
  for (int i = 3; i*i < SQR; i+=2)
    if (!Q[i])
      for (int j = i*i; j < SQR; j += 2*i)
        Q[j] = 1;
  // segmented sieve
  vector<int> primes(1,2);
  vector< pair<int,int> > P; // (2 * prime, next to sieve)
  for (int s = 3, k = 3, low = 0; low < n; low += M) {
    int high = min(low + M, n);
    bool *S = buf - low;
    memset(buf, 0, sizeof(buf));
    for (; s*s < high; s+=2)
      if (!Q[s]) P.push_back(make_pair(2*s, s*s));
    FOR(p, P) for (; p->snd < high; p->snd += p->fst) S[p->snd] = 1;
    for (; k < high; k+=2)
      if (!S[k]) primes.push_back(k);
    if (primes.size() > 5000000) break;
  }
  return primes;
}

int main() {
  vector<int> p = primeList(100000000);
  int T; scanf("%d", &T);
  while (T--) {
    int k; scanf("%d", &k);
    printf("%d\n", p[k-1]);
  }
}
