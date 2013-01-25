// SPOJ 1112: Number Steps
// http://www.spoj.com/problems/NSTEPS/
//
// Solution: Ad-hoc

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int solve(int x, int y) {
  if (x == y) {
    // y 0 1 2 3 4 5
    // r 0 1 4 5 8 9 ...
    return y * 2 - (y % 2);
  } 
  if (x == y + 2) {
    // y 0 1 2 3 4   5
    // r 2 3 6 7 10 11 ...
    return y * 2 + 2 - (y % 2);
  }
  return -1;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int x, y; scanf("%d %d", &x, &y);
    int r = solve(x, y);
    if (r < 0) printf("No Number\n");
    else printf("%d\n", r);
  }
}
