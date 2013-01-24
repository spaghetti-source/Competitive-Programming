// SPOJ 7974: What's next
// http://www.spoj.com/problems/ACPC10A/
//
// Solution: trivial
//

#include <cstdio>

using namespace std;

int main() {
  int a, b, c;
  while (scanf("%d %d %d", &a, &b, &c) == 3) {
    if (a == 0 && b == 0 && c == 0) break;
    if (a - b == b - c) {
      printf("AP %d\n", c + b - a);
    } else {
      printf("GP %d\n", c * b / a);
    }
  }
}
