// SPOJ 21418: Interesting Game with Polygons
// http://www.spoj.com/problems/HCT00001/
//
// Solution: grundy number
//
// basically: 
//   select a side     ==> n-gon -> (n-3)-gon
//   select a diagonal ==> split n-gon into n_1-gon and n_2-gon

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <unordered_set>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int mex(const unordered_set<int> &x) {
  for (int i = 0; ; ++i)
    if (!x.count(i)) return i;
}
int f(int k) {
  if (k <= 2) return 0;
  if (k == 3) return 1;
  return k - 1;
}
int cache[1010];
int grundy(int n) {
  if (n <= 0) return 0;
  if (n <= 3) return 1;
  if (cache[n] >= 0) return cache[n];
  unordered_set<int> adj;
  adj.insert(grundy(f(n-1))); // select a side
  for (int k = 2; n-k >= 2; ++k) 
    adj.insert(grundy(f(k))^grundy(f(n-k)));
  return cache[n] = mex(adj);
}

int main() {
  fill(cache, cache+1010, -1);
  int n; 
  scanf("%d", &n);
  if (n == 1) printf("2\n");
  else printf("%d\n", grundy(n) == 0 ? 2 : 1);
}
