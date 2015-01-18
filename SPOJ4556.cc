// SPOJ 4556: Think I will Buy Me a Football Team
// http://www.spoj.com/problems/ANARC08G/
//
// Solution: ad-hoc

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

void doit(int n) {
  vector<int> res(n);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int a; scanf("%d", &a);
      sum += a;
      res[i] += a;
      res[j] -= a;
    }
  }
  int red = 0;
  for (int i = 0; i < n; ++i) 
    red += max(res[i], 0);
  printf("%d %d\n", sum, red);
}
int main() {
  for (int icase = 0; ; ++icase) {
    int n; scanf("%d", &n);
    if (n == 0) break;
    printf("%d. ", icase+1);
    doit(n);
  }
}
