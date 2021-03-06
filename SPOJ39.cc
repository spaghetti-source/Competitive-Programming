// SPOJ 39: Piggy-Bank
// http://www.spoj.com/problems/PIGBANK/
//
// Solution: DP (knapsack)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

const int INF = 99999999;

int knapsack(vector<int> v, vector<int> w, int W) {
  int n = v.size();
  vector<int> F(W+1, INF); F[0] = 0;
  for (int i = 0; i < n; ++i)
    for (int a = w[i]; a <= W; ++a) // multiple use of same item
      F[a] = min(F[a], F[a-w[i]] + v[i]);
  return F[W];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n, W; scanf("%d %d", &n, &W); W -= n;
    scanf("%d", &n);
    vector<int> v(n), w(n);
    for (int i = 0; i < n; ++i)
      scanf("%d %d", &v[i], &w[i]);
    int x = knapsack(v, w, W);
    if (x >= INF) printf("This is impossible.\n");
    else printf("The minimum amount of money in the piggy-bank is %d.\n", x);
  }
}
