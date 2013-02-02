// SPOJ 3638: Word Counting
// http://www.spoj.com/problems/WORDCNT/
//
// Solution: ad-hoc

#include <iostream>
#include <sstream>
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

int main() {
  string s;
  getline(cin, s);
  int T; 
  sscanf(s.c_str(), "%d", &T);
  while (T--) {
    getline(cin, s);
    stringstream ss(s);

    int len = -1;
    int cnt, maxcnt = 0;
    while (ss >> s) {
      if (s.size() != len) {
        len = s.size();
        cnt = 0;
      }
      maxcnt = max(maxcnt, ++cnt);
    }
    printf("%d\n", maxcnt);
  }
}
