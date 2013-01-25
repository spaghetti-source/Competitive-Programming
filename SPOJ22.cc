// SPOJ 25: Pouring Water
// http://www.spoj.com/problems/POUR1/
//
// Solution: Math, simulation
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
  for (; a; swap(b %= a, a));
  return b;
}
// only a -> b move
int solve2(int a, int b, int c) {
  int ans = 0, x = 0, y = 0; // x: amount in a, y: amount in b
  while (x != c && y != c) {
    if (x == 0) {
      x = a; ++ans; 
    } else if (y == b) {
      y = 0; ++ans; 
    } else {
      int p = min(x, b-y); 
      x -= p; y += p; ++ans;
    }
  }
  return ans;
}
int solve(int a, int b, int c) {
  if (c == 0) return 0;
  if (c > a && c > b) return -1;
  if (c % gcd(a,b)) return -1;
  return min(solve2(a,b,c), solve2(b,a,c));
}
int main() {
  int t; scanf("%d", &t);
  while (t--) {
    int a, b, c; scanf("%d %d %d", &a, &b, &c);
    printf("%d\n", solve(a,b,c));
  }
}
