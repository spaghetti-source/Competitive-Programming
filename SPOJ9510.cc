// SPOJ 9510: Ads Proposal
// http://www.spoj.com/problems/ADSPROP/
//
// Solution: ad-hoc (accumulation)

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

void doit() {
  int N, M, Q;
  scanf("%d %d %d", &N, &M, &Q);
  vector< pair<LL, LL> > A[N];
  REP(m, M) {
    int U, C, L;
    scanf("%d %d %d", &U, &C, &L);
    A[U-1].push_back(make_pair(C, L));
  }
  int maxlen = 0;
  REP(n, N) {
    sort(ALL(A[n]));
    reverse(ALL(A[n]));
    maxlen = max(maxlen, (int)A[n].size());
  }
  vector<LL> B(maxlen);
  REP(n, N) 
    REP(i, A[n].size())
      B[i] += A[n][i].snd;

  vector<LL> S(maxlen+1);
  REP(k, maxlen) 
    S[k+1] = S[k] + B[k];

  REP(q, Q) {
    int K;
    scanf("%d", &K);
    K = min(K, (int)(S.size()-1));
    printf("%lld\n", S[K]);
  }
}

int main() {
  int T; scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    printf("Case #%d:\n", t);
    doit();
  }
}
