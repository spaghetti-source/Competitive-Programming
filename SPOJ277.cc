// SPOJ 277: City Game
// http://www.spoj.com/problems/CTGAME/
//
// Solution: All nearest smaller values

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <stack>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

template <class T>
vector<int> nearest_smallers(const vector<T> &x) {
  vector<int> z;
  for (int i = 0; i < x.size(); ++i) {
    int j = i-1;
    while (j >= 0 && x[j] >= x[i]) j = z[j];
    z.push_back(j);
  }
  return z;
}

// from SPOJ1805
long long maximum_histogram(vector<long long> x) {
  auto v = nearest_smallers(x);
  reverse(all(x));
  auto u = nearest_smallers(x);
  reverse(all(x));
  reverse(all(u));
  long long best = 0;
  for (int i = 0; i < x.size(); ++i) {
    long long area = x[i] * (x.size() - v[i] - u[i] - 2);
    best = max(best, area);
  }
  return best;
}

int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int n, m; scanf("%d %d", &n, &m);
    vector<long long> a(m);
    long long best = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        char c[128]; scanf("%s", c);
        if (c[0] == 'R') a[j] = 0; else ++a[j];
      }
      best = max(best, maximum_histogram(a));
    }
    printf("%lld\n", 3*best);
  }
}
