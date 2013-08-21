// SPOJ 5449: Seinfeld
// http://www.spoj.com/problems/ANARC09A/
//
// Solution: adhoc, sequence
//
// Count the left and right parenthes:
//   if '{', c += 1
//   if '}', c -= 1
//
// if c < 0, modify current '}' to '{'.
// if c > rest of string, modify '{' to '}'
//

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

int solve(char s[]) {
  int n = strlen(s);
  int c = 0, m = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '{') ++c;
    if (s[i] == '}') --c;
    if (c < 0) { ++m; c += 2; }
    if (c >= n - i) { ++m; c -= 2; }
  }
  return m;
}

int main() {
  char buf[2010];
  for (int T = 1; gets(buf); ++T) {
    if (buf[0] == '-') break;
    printf("%d. %d\n", T, solve(buf));
  }
}
