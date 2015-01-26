// SPOJ 17731: Buying Integers
// http://www.spoj.com/problems/BUYINT/
//
// Solution: math

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef long long ll;

ll f(ll n, ll k) {
  ll odd  = k*(k-1)/2 + (n-k)*(n-k-1)/2;
  ll even = n * (n-1)/2 - odd;
  if (odd > even) return odd - even;
  else            return even - odd;
}
// 10^18

void doit(ll n) {
  ll k = (n + sqrt(n))/2;
  while (f(n,k) > f(n,k-1)) --k;
  while (f(n,k) > f(n,k+1)) ++k;
  printf("%lld\n", f(n,k));
}
int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    printf("Case %d: ", icase+1);
    ll n; scanf("%lld", &n);
    doit(n);
  }
}
