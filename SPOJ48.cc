// SPOJ 48: Glass Beads
// http://www.spoj.com/problems/BEADS/
//
// Solution: String (minimum expression)
//
// Same as SPOJ 3605: Minimum Rotations
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

// Zhou-Yuan ?
//
// References:
// - R. Sedgewick: Algorithm, 4th eds. ?
//
int minimumExpression(string s) {
  int n = s.size(), i = 0, j = 1, k = 0;
  while (i+k < 2*n && j + k < 2*n) {
    char a = i+k<n?s[i+k]:s[i+k-n], b = j+k<n?s[j+k]:s[j+k-n]; // mod n
    if      (a > b) { i += k+1; k = 0; if (i <= j) i = j+1; }
    else if (a < b) { j += k+1; k = 0; if (j <= i) j = i+1; }
    else ++k;
  }
  return min(i, j);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    string s; cin >> s;
    cout << minimumExpression(s)+1 << endl;
  }
}
