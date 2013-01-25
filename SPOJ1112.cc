// SPOJ 13043: The Mirror of Galadriel
// http://www.spoj.com/problems/AMR12D/
//
// Solution: String
//
// since substrings of length n string is O(n^2),
// simple method is acceptable.

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

bool solve(string s) {
  set<string> S;
  int n = s.size();
  for (int i = 0; i < n; ++i) 
    for (int l = 1; i+l <= n; ++l) 
      S.insert( s.substr(i,l) );
  for (int i = 0; i < n; ++i) 
    for (int l = 1; i+l <= n; ++l) {
      string r = s.substr(i,l);
      reverse(r.begin(), r.end());
      if (S.count(r) == 0) return false;
    }
  return true;
}

int main() {
  int T; cin >> T;
  while (T--) {
    string s; cin >> s;
    if (solve(s)) printf("YES\n");
    else          printf("NO\n");
  }
}
