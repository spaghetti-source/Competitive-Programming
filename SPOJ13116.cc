// SPOJ 13116: Dividing Xorland
// http://www.spoj.com/problems/PUCMM333/
//
// Solution: brute force

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int n;
int T[10][10];

vector<int> region(int i, int j) {
  vector<int> x;
  for (; i < j; ++i) 
    for (int k = 0; k < n; ++k)
      x.push_back(T[i][k]);
  return x;
}

int max_xor(vector<int> x) {
  set<int> curr;
  curr.insert(0);
  for (int i = 0; i < x.size(); ++i) {
    int a = x[i];
    set<int> next = curr;
    for (set<int>::iterator it = curr.begin(); it != curr.end(); ++it) {
      int v = *it;
      next.insert(a ^ v);
    }
    curr.swap(next);
  }
  int ans = *max_element(all(curr));
  return ans;
}

void gen() {
  n = 3 + rand() % 3;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      T[i][j] = 1 + rand() % 100000;
}

int main() {
  //gen();
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%d", &T[i][j]);

  // [0,i), [i,j), [j,n)
  int ans = 0;
  for (int i = 1; i < n; ++i) 
    for (int j = i+1; j < n; ++j) 
      ans = max(ans, max_xor(region(0,i))
                   + max_xor(region(i,j))
                   + max_xor(region(j,n)));
  for (int i = 0; i < n; ++i)
    for (int j = i+1; j < n; ++j)
      swap(T[i][j], T[j][i]);
  for (int i = 1; i < n; ++i) 
    for (int j = i+1; j < n; ++j) 
      ans = max(ans, max_xor(region(0,i))
                   + max_xor(region(i,j))
                   + max_xor(region(j,n)));
  printf("%d\n", ans);
}
