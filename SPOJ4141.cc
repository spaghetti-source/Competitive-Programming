// SPOJ 4141: Euler Totient Function
// http://www.spoj.com/problems/ETF/
//
// Solution: Sieve
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

#include <ctime>

using namespace std;

int eulerPhi(int n) {
  const int N = 1000001;
  static int once, sieve[N/2], phi[N/2];
  if (!once++) {
    for (int i = 1; i < N; i+=2)
      sieve[i/2] = phi[i/2] = i;
    for (int i = 3; i < N; i+=2) {
      if (sieve[i/2]) {
        for (int j = i; j < N; j+=2*i) {
          sieve[j/2] = 0;
          phi[j/2] -= phi[j/2] / i;
        }
      }
    }
  }
  int lsb = n & -n; // = factor 2
  return lsb > 1 ? lsb / 2 * phi[n / lsb / 2] : phi[n / 2];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    printf("%d\n", eulerPhi(n));
  }
}
