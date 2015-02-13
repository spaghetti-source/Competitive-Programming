// SPOJ 21683: Bhagat and String
// http://www.spoj.com/problems/BGTSTR/
//
// Solution: rolling hash

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef long long ll;
struct rolling_hash {
  static const unsigned long long p = 1000000007ull;
  const char *s;
  int n;
  vector<ll> pow, phash;
  rolling_hash(const char *s) : s(s), n(strlen(s)), pow(n+1), phash(n+1) {
    pow[0] = 1; phash[0] = 0;
    for (int i = 0; i < n; ++i) {
      phash[i+1] = s[i] + phash[i] * p;
      pow[i+1] = pow[i] * p;
    }
  }
  ll hash(int i, int j) {
    return phash[j] - phash[i] * pow[j-i];
  }
};
void solve(char s[], int k) {
  int n = strlen(s);
  rolling_hash RH(s);

  int lo = 0, hi = n+1, l;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    unordered_map<ll, int> bucket;
    l = -1;
    for (int i = 0; i+mid <= n; ++i) 
      if (++bucket[RH.hash(i, i+mid)] >= k) l = i;
    if (l == -1) hi = mid;
    else         lo = mid;
  }
  unordered_map<ll, int> bucket;
  l = -1;
  for (int i = 0; i+lo <= n; ++i) 
    if (++bucket[RH.hash(i, i+lo)] >= k) l = i;

  if (lo == 0) {
    printf("HATE\n");
  } else {
    printf("%d %d\n", lo, l+1);
  }
}
int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    char s[50010];
    scanf("%s", s);
    int k;
    scanf("%d", &k);
    solve(s, k);
  }
}
