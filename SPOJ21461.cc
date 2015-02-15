// SPOJ 21461: Field
// http://www.spoj.com/problems/NPC2014F/
//
// Solution: windowing

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int main() {
  int n; scanf("%d", &n);
  char s[100010]; scanf("%s", s);
  int k; scanf("%d", &k);
  int x[0x100] = {0};
  for (int i = 0; i < k; ++i) {
    int a; 
    char c[10];
    scanf("%d %s", &a, c);
    x[c[0]] = a;
  }

  int z[0x100] = {0};
  int cond = 0;
  int i = 0, j = 0;
  int opt = n+1;
  while (i < n) {
    while (cond < k && j < n) {
      char c = s[j++];
      if (++z[c] == x[c]) ++cond;
    }
    if (cond >= k) {
      opt = min(opt, j - i);
    }
    char c = s[i++];
    if (z[c]-- == x[c]) --cond;
  }
  if (opt > n) printf("Andy rapopo\n");
  else         printf("%d\n", opt);
}
