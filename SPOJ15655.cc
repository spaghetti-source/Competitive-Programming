// SPOJ 15655: Product of factorials
// http://www.spoj.com/problems/FACTMUL/
//
// Solution: trick question (M is non-prime), ad-hoc

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

typedef long long LL; 
const LL M = 109546051211ll;
// 109546051211 = 186583 * 587117

LL mulMod(LL a, LL b, LL M) {
  LL r = a*b - LL(double(a)*b/M + 0.5)*M;
  while (r < 0) r += M;
  return r;
}
int main() {
  LL f = 1, p = 1;
  int n; cin >> n;
  for (int i = 1; p && i <= n; ++i) {
    f = (f * i) % M;
    p = mulMod(p, f, M); 
  }
  cout << p << endl;
}
