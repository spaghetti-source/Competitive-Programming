// SPOJ 9032. Cube Free Numbers
// http://www.spoj.com/problems/CUBEFR/
//
// Solution: DP (sieve)

#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 1100000;
int cube[N];
int id[N], num = 0;

int main() {
  // precalc.
  for (int i = 2; i*i*i < N; ++i)
    for (int j = i*i*i; j < N; j+=i*i*i)
      cube[j] = 1;
  for (int i = 1; i < N; ++i)
    if (!cube[i]) id[i] = ++num;

  int T; scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    int n; scanf("%d", &n);
    printf("Case %d: ", t);
    if (!cube[n]) printf("%d\n", id[n]);
    else printf("Not Cube Free\n");
  }
}
