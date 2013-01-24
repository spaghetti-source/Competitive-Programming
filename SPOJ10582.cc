// SPOJ 10582: subarrays
// http://www.spoj.com/problems/ARRAYSUB/
//
// Solution: Windowing with BST
//

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
  int n, k;
  scanf("%d", &n);
  vector<int> a(n+1);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  scanf("%d", &k);

  multiset<int> S;
  for (int i = 0; i < k; ++i)
    S.insert(a[i]);

  for (int i = k; i <= n; ++i) {
    printf("%d", *S.rbegin());
    if (i + 1 <= n) printf(" ");
    S.erase( S.find(a[i-k]) );
    S.insert(a[i]);
  }
}
