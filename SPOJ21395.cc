// SPOJ 21395: Ohani And Binary Search Tree
// http://www.spoj.com/problems/OHANIBTR/
//
// Solution: optimal insertion sort, complete bst

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

template <class T>
int longest_increasing_subsequence(const vector<T> &x) {
  int n = x.size();
  vector<int> length(n), tail;
  for (int k = 0; k < n; ++k) {
    length[k] = distance(tail.begin(), upper_bound(all(tail), k, 
      [&](int i, int j) { return x[i] < x[j]; }
    ));
    if (length[k] == tail.size()) tail.push_back(k);
    else                          tail[length[k]] = k;
  }
  return *max_element(all(length)) + 1;
}

vector<int> completeBST(int n) {
  vector<int> p(n, -1);
  function<void (int,int,int)> rec = [&](int i, int j, int q) {
    if (j <= i) return;
    if (j == i + 1) {
      p[i] = q;
    } else {
      int n = j - i, k = 1;
      while (2*k <= n) k *= 2;
      if (k/2 - 1 <= (n-k)) k = k - 1;
      else                  k = n - k/2;
      p[i+k] = q;
      rec(i, i+k, i+k);
      rec(i+k+1, j, i+k);
    }
  };
  rec(0, n, -1);
  return p;
}

int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    printf("Case %d:\n", icase+1);
    int n; scanf("%d", &n);
    vector<int> x(n);
    for (int i = 0; i < n; ++i) 
      scanf("%d", &x[i]);
    printf("Minimum Move: %d\n", n - longest_increasing_subsequence(x));
    sort(all(x));
    vector<int> p = completeBST(n);
    for (int i = 0; i < n; ++i) {
      if (i > 0) printf(" ");
      if (p[i] < 0) printf("-1");
      else          printf("%d", x[p[i]]);
    }
    printf("\n");
  }
}
