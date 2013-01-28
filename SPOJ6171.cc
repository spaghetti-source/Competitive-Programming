// SPOJ 6171: Majority
// http://www.spoj.com/problems/MAJOR/
//
// Solution: Bucket
//
// Remark: perhaps, IO hard

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

int C[3000];
const int S = 1010;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    memset(C, 0, sizeof(C));
    int n; scanf("%d", &n);
    int b, m = 0;
    for (int i = 0; i < n; ++i) {
      int a; scanf("%d", &a);
      if (++C[a + S] > m) { m = C[a + S]; b = a; }
    }
    if (2 * m > n) printf("YES %d\n", b);
    else printf("NO\n");
  }

}
