// SPOJ 27: Sorting Bank Accounts
// http://www.spoj.com/problems/SBANK/
//
// Solution: String 
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)

char s[10000];

int main() {
  int T; scanf("%d", &T);
  for (int t = 0; t < T; ++t) {
    if (t > 0) printf("\n");
    int n; scanf("%d\n", &n);
    map<string, int> M;
    while (n--) {
      gets(s);
      M[(string)s]++;
    }
    FOR(i,M) printf("%s %d\n", i->first.c_str(), i->second);
  }
}
