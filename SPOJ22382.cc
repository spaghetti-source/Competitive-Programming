// SPOJ 22382: Euler Totient Function Depth
// http://www.spoj.com/problems/ETFD/
//
// Solution: euler totient function 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef long long ll;

ll euler_phi(ll n) {
  if (n == 0) return 0;
  ll ans = n;
  for (ll x = 2; x*x <= n; ++x) {
    if (n % x == 0) {
      ans -= ans / x;
      while (n % x == 0) n /= x;
    }
  }
  if (n > 1) ans -= ans / n;
  return ans;
}

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
vector<ll> euler_phi(ll lo, ll hi) { // phi(n) for all n in [lo, hi)
  vector<ll> ps = primes(sqrt(hi)+1);
  vector<ll> res(hi-lo), phi(hi-lo, 1);
  iota(all(res), lo);
  for (ll p: ps) {
    for (ll k = ceil(1.0*lo/p)*p; k < hi; k += p) {
      if (res[k-lo] < p) continue;
      phi[k-lo] *= (p - 1);
      res[k-lo] /= p;
      while (res[k-lo] > 1 && res[k-lo] % p == 0) {
        phi[k-lo] *= p;
        res[k-lo] /= p; 
      }
    }
  }
  for (ll k = lo; k < hi; ++k) {
    if (res[k-lo] > 1) 
      phi[k-lo] *= (res[k-lo]-1);
  }
  return phi; // phi[k-lo] = phi(k)
}
vector<ll> phi;
vector<int> depth;
int calc(int n) {
  if (depth[n] > 0) return depth[n];
  if (n <= 1) return depth[n] = n-1;
  return depth[n] = calc(phi[n]) + 1;
}
const int N = 1000000;
unordered_map<int, vector<int>> result;
void precompute() {
  phi = euler_phi(0, N+1);
  depth.assign(N+1, -1);
  for (int i = 0; i < N+1; ++i) 
    result[calc(i)].push_back(i);
}
int solve(int m, int n, int k) {
  return distance(lower_bound(all(result[k]), m), 
                  lower_bound(all(result[k]), n));
}
int main() {
  precompute();
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    printf("%d\n", solve(m, n+1, k));
  }
}
