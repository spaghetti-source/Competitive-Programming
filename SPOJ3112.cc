// SPOJ 3112: Strings
// http://www.spoj.com/problems/STSTRING/
//
// Solution: ad-hoc
//
// Trick: compare with length and then with lexicographic order
//    <=>
//        compare "length ++ string" with lexicographic order

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


string encode(string s) {
  string h; h += ('0'+s.size());
  return h + s;
}

vector<string> S;
void gen(char s[], int n, int i) {
  if (i == n) {
    S.push_back(encode(s));
    return;
  }
  for (char c = 'A'; c <= 'J'; ++c) {
    s[i] = c;
    if (i == 0 || abs(s[i] - s[i-1]) > 1) gen(s, n, i+1);
    s[i] = '_';
  }
}
void init() {
  char s[10];
  memset(s, 0, sizeof(s));
  REP(l, 6) gen(s, l+1, 0);
}
bool Compare(string s, string t) {
  if (s.size() != t.size()) return s.size() < t.size();
  return s < t;
}

int main() {
  init();
  for (string s, t; cin >> s >> t; ) {
    s = encode(s);
    t = encode(t);
    int x = lower_bound(ALL(S), t) - upper_bound(ALL(S), s);
    cout << max(x, 0) << endl;
  }
}
