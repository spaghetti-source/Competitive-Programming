// SPOJ 3442: The last digit
// http://www.spoj.com/problems/LASTDIG/
//
// Solution: Math (powmod)
//
// To fit into 700B, remove this comment.
#include <cstdio>
using namespace std;
typedef long long LL;
int main() {
  int T; scanf("%d", &T);
  while (T--) {
    LL a, b, x = 1; scanf("%lld %lld", &a, &b);
    for (; b > 0; b >>= 1) {
      if (b & 1) x = (x * a) % 10;
      a = (a * a) % 10;
    }
    printf("%lld\n", x);
  }
}
