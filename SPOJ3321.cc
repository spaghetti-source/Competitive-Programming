// SPOJ 3321: Knapsack Problem
// http://www.spoj.com/problems/KNAPSACK/
//
// Solution: DP(knapsack)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


// Weight DP
// Complexity: O(nW)
//
// F[a] := maximum value for weight a
//
// Verified
//   SPOJ 3321. The Knapsack Problem
int knapsack(vector<int> v, vector<int> w, int W) {
  int n = v.size();
  vector<int> F(W+1);
  for (int i = 0; i < n; ++i)
    for (int a = W; a >= w[i]; --a)
      F[a] = max(F[a], F[a-w[i]] + v[i]);
  return F[W];
}

int main() {
  int W, n;
  scanf("%d %d", &W, &n);
  vector<int> v(n), w(n);
  for (int i = 0; i < n; ++i) 
    scanf("%d %d", &w[i], &v[i]);
  printf("%d\n", knapsack(v, w, W));
}
