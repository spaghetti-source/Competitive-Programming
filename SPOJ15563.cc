// SPOJ 15563: Check the string Powers
// http://www.spoj.com/problems/IITKWPCJ/
//
// Solution: sorting, rolling hash

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
  vector<ULL> pow, phash;
  RollingHash(string s) : s(s), n(s.size()), pow(n+1), phash(n+1) {
    pow[0] = 1; phash[0] = 0;
    REP(i, n) {
      phash[i+1] = s[i] + phash[i] * p;
      pow[i+1] = pow[i] * p;
    }
  }
  // hash of s[i,j) 
  ULL hash(int i, int j) {
    return phash[j] - phash[i] * pow[j-i];
  }
  ULL hash(string t) {
    ULL h = 0;
    REP(i, t.size()) h = t[i] + h * p;
    return h;
  }
};

bool solve(string s, string t) {
  if (s.size() > t.size()) swap(s, t);
  int n = s.size(), m = t.size();
  RollingHash RH(t+t);
  ULL h = RH.hash(s);
  int i = 0;
  do {
    if (h != RH.hash(i, i+n)) return false;
    i = (i + n) % m;
  } while (i > 0);
  return true;
}

int main() {
  int n; cin >> n;
  while (n--) {
    string s, t;
    cin >> s >> t;
    cout << (solve(s, t) ? "YES" : "NO") << endl;
  }
}
