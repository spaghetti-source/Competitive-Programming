// SPOJ 22461: Smallest Number
// http://www.spoj.com/problems/SMALL/
//
// Solution: prime factorization

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef long long ll;
vector<ll> primes(ll lo, ll hi) { // primes in [lo, hi)
  const ll M = 1 << 14, SQR = 1 << 16;
  vector<bool> composite(M), small_composite(SQR);

  vector<pair<ll,ll>> sieve; 
  for (ll i = 3; i < SQR; i+=2) {
    if (!small_composite[i]) {
      ll k = i*i + 2*i*max(0.0, ceil((lo - i*i)/(2.0*i)));
      sieve.push_back({2*i, k});
      for (ll j = i*i; j < SQR; j += 2*i) 
        small_composite[j] = 1;
    }
  }
  vector<ll> ps; 
  if (lo <= 2) { ps.push_back(2); lo = 3; }
  for (ll k = lo|1, low = lo; low < hi; low += M) {
    ll high = min(low + M, hi);
    fill(all(composite), 0);
    for (auto &z: sieve) 
      for (; z.snd < high; z.snd += z.fst)
        composite[z.snd - low] = 1;
    for (; k < high; k+=2) 
      if (!composite[k - low]) ps.push_back(k);
  }
  return ps;
}
vector<ll> primes(ll n) { // primes in [0,n)
  return primes(0,n);
}
vector<ll> ps;

const ll M = 1000000007;
ll mul(ll a, ll b, ll M) {
  ll r = a*b - floor(1.0*a*b/M)*M;
  return r < 0 ? r + M : r >= M ? r - M : r;
}

void doit() {
  ll n; scanf("%lld", &n);
  ll ans = 1;
  for (ll p: ps) {
    ll q = 1;
    while (p * q <= n) q *= p;
    ans = mul(ans, q, M);
  }
  printf("%lld\n", ans);
}
int main() {
  ps = primes(10010);
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) doit();
}
