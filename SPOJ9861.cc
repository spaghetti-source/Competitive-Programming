// SPOJ 9861: Hotels Along the Croatian Coast
// http://www.spoj.com/problems/HOTELS/
//
// Solution: windowing
//
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

using namespace std;

int main() {
  int n;
  long long m;
  scanf("%d %lld", &n, &m);
  vector<long long> a(n);
  for (int i = 0; i < n; ++i)
    scanf("%lld", &a[i]);

  long long best = -1;
  long long curr = 0;
  for (int i = 0, j = 0; i < n; ) {
    if (j < n && curr < m) curr += a[j++];
    else                   curr -= a[i++];  
    if (curr <= m) best = max(best, curr);
  }
  printf("%d\n", best);
}
