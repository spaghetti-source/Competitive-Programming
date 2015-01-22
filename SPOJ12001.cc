// SPOJ 12001: Bit by Bit
// http://www.spoj.com/problems/DCEPC807/
//
// Solution: dynamic programming
//
// Note: F(n) = n 2^n. 
// Thus F(n) is a power of two iff n is a power of two.

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

vector<int> _win;
bool win(int n) {
  if (_win[n] >= 0) return _win[n];
  if ((n & (n-1)) == 0) return false; 
  for (int b = 1; b < n; b <<= 1) 
    if ((n & b) == b && !win(n ^ b)) return _win[n] = true;
  for (int b = 3; b <= n; b <<= 1) 
    if ((n & b) == b && !win(n ^ b)) return _win[n] = true;
  return _win[n] = false;
}
void doit() {
  int n; scanf("%d", &n);
  if (win(n)) printf("Alice\n"); 
  else        printf("Bob\n");
}
int main() {
  _win.resize(1000010,-1);
  int T; scanf("%d", &T);
  while (T--) doit();
}
