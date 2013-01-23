// SPOJ 13432: Even
//
// Solution: Ad-Hoc

#include <cstdio>

using namespace std;

int main() {
  int n; 
  while (scanf("%d", &n) == 1) {
    printf("%d\n", !(n & 1));
  }
}
