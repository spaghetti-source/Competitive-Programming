// SPOJ 1805: Largest Rectangels in a Histogram
// http://www.spoj.com/problems/HISTOGRA/
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
int main() {
  for (int n; scanf("%d", &n) == 1 && n > 0; ) {
    vector<long long> x(n);
    for (int i = 0; i < n; ++i) 
      scanf("%lld", &x[i]);
    auto v = nearest_smallers(x);
    reverse(all(x));
    auto u = nearest_smallers(x);
    reverse(all(x));
    reverse(all(u));
    long long best = 0;
    for (int i = 0; i < n; ++i) {
      long long area = x[i] * (n - v[i] - u[i] - 2);
      best = max(best, area);
    }
    printf("%lld\n", best);
  }
}
