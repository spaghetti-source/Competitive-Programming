// SPOJ 22455: SUM OF PRODUCT
// http://www.spoj.com/problems/SUMPRO/
//
// Solution: math (OEIS)
// see: https://oeis.org/A024916
//

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef long long ll;

ll add(ll a, ll b, ll M) {
  a += b;
  if (a >= M) a -= M;
  return a;
}
ll sub(ll a, ll b, ll M) { 
  if (a < b) a += M;
  return a - b;
}
ll mul(ll a, ll b, ll M) {
  ll r = a*b - (ll)((long double)(a)*b/M)*M;
  return r < 0 ? r + M : r >= M ? r - M : r;
}
const ll M = 1000000007;
ll solve(ll n) {
  ll s = 0, d = 1, q = n;
  while (d < q) {
    s = add(s, (q*(q+1+2*d)/2)%M, M);
    ++d;
    q = n / d;
  }
  return sub(add(s, (q*(q+1)/2)%M, M), (d*(d-1)/2*d)%M, M);
}


int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    ll n; scanf("%lld", &n);
    printf("%lld\n", solve(n));
  }
}
