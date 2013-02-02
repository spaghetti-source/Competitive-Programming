// SPOJ 694: Distinct Substrings
// http://www.spoj.com/problems/DISUBSTR/
//
// Solution: Suffix Array

#include <iostream>
#include <sstream>
#include <cstdio>
#include <set>
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
  vector<ULL> pow, phash;
  RollingHash(string s) : s(s), n(s.size()), 
    pow(n+1,1), phash(n+1,0) {
    REP(i, n) {
      phash[i+1] = s[i] + phash[i] * p;
      pow[i+1] = pow[i] * p;
    }
  }
  ULL hash(int i, int j) { // hash of s[i,j) 
    return phash[j] - phash[i] * pow[j-i];
  }
  int lcp(int i, int j) {
    int l = 0, r = min(n-i, n-j)+1;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (hash(i,i+m) == hash(j,j+m)) l = m;
      else                            r = m;
    }
    return l;
  }
  bool operator()(int i, int j) { // sort(ALL(sa), R) -> suffix array
    int k = lcp(i, j);
    return i+k >= n ? true : j+k >= n ? false : s[i+k] <= s[j+k];
  }
};

int main() {
  int T; cin >> T;
  while (T--) {
    string s; cin >> s;
    int n = s.size();
    RollingHash R(s);
    vector<int> sa(n);
    REP(i, n) sa[i] = i;
    sort(ALL(sa), R); // suffix array

    ULL t = 0;
    for (int i = 0; i+1 < n; ++i) 
      t += R.lcp(sa[i], sa[i+1]);
    cout << n*(n+1)/2 - t << endl;
  }
}
