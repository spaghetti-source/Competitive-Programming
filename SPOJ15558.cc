// SPOJ 15558: Let us play with strings
// http://www.spoj.com/problems/IITKWPCE/
//
// Solution: DP, string (rolling hash)
//
// opt s[0,i) = min { opt [0,j) + 1 : [i,j) is palindrome }
// substring palindromicity can be checked by a rolling hash.

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

typedef unsigned long long ULL;
struct RollingHash {
  static const ULL p = 1000000007ULL;
  string s;
  int n;
  vector<ULL> pow, phash, rhash;
  RollingHash(string s) : s(s), n(s.size()), 
    pow(n+1), phash(n+1), rhash(n+1) {
    pow[0] = 1; phash[0] = 0; rhash[n] = 0;
    REP(i, n) {
      phash[i+1] = s[i] + phash[i] * p;
      rhash[n-i-1] = s[n-i-1] + rhash[n-i] * p;
      pow[i+1] = pow[i] * p;
    }
  }
  bool isPalindrome(int i, int j) {
    ULL a = phash[j] - phash[i] * pow[j-i];
    ULL b = rhash[i] - rhash[j] * pow[j-i];
    return a == b;
  }
};

//
// f s[0,k) = min { 1 + f s[0,i) : [i,k) is parindrome }
int solve(string s) {
  int n = s.size();
  RollingHash RH(s);
  vector<int> c(n+1, n);
  c[0] = 0;
  for (int k = 1; k <= n; ++k) {
    for (int i = 0; i <= k; ++i) {
      if (RH.isPalindrome(i, k))
        c[k] = min(c[k], 1 + c[i]);
    }
  }
  return c[n];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    char buf[2010];
    scanf("%s", buf);
    printf("%d\n", solve(buf));
  }
}
