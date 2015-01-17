// SPOJ 21347: Tulip And Numbers
// http://www.spoj.com/problems/TULIPNUM/
//
// Solution: adhoc

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
  int ncase;
  scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    printf("Case %d:\n", icase+1);
    int n, q;
    scanf("%d %d", &n, &q);

    int x=-1, num[n+1]; 
    num[0] = 0;
    for (int i = 0; i < n; ++i) {
      int y; scanf("%d", &y);
      num[i+1] = num[i] + (x != y);
      x = y;
    }
    
    for (int k = 0; k < q; ++k) {
      int i, j;
      scanf("%d %d", &i, &j);
      int ans = num[j] - num[i-1] + (num[i] == num[i-1]);
      printf("%d\n", ans);
    }
  }
}

