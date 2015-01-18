// SPOJ 7406: Beehive Numbers
// http://www.spoj.com/problems/BEENUMS/
//
// Solution: trivial

#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <algorithm>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

unordered_set<long long> table;
void update(long long n) {
  static long long k, m;
  for (; m < n; ++k) {
    m = 3*k*k + 3*k + 1;
    table.insert(m);
  }
}
int main() {
  for (long long n; scanf("%lld", &n); ) {
    if (n < 0) break;
    update(n);
    printf("%s\n", table.count(n) ? "Y" : "N");
  }
}
