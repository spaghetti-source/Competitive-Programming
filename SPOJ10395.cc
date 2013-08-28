// SPOJ 10395: Sum of divisors!
// http://www.spoj.com/problems/ABA12D/
//
// Solution: math (number theory)
//
// sumdiv = (1 + p + p^2 + ...) (1 + q + q^2 + ...) ...
//
// This number is prime only if it is a prime power.
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

const int N = 1000010;

// optimized segmented sieve; limitation: n < 10^8
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
  }
  return primes;
}
vector<int> primes;
bool isPrime(int n) { return binary_search(ALL(primes), n); }

int main() {
  tick();
  primes = primeList(N);
  vector<int> Knum;
  for (int i = 0; primes[i]*primes[i] < N; ++i) {
    LL sigma = 1;
    for (LL p = primes[i]; p < N; p *= primes[i]) {
      sigma += p; // == sigma(p)
      if (isPrime(sigma)) Knum.push_back(p);
    }
  }
  sort(ALL(Knum));
  int T;
  scanf("%d", &T);
  while (T--) {
    int a, b;
    scanf("%d %d", &a, &b);
    int c = upper_bound(ALL(Knum), b) - lower_bound(ALL(Knum), a);
    printf("%d\n", c);
  }
}
