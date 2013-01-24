// SPOJ 3032: Adding two numbers
// http://www.spoj.com/problems/ADUN/
//
// Solution: trivial
//
// 2,100,000,000 <= 2^31

#include <cstdio>

using namespace std;

int main() {
  unsigned int a, b;
  scanf("%u %u", &a, &b);
  printf("%u\n", a + b);
}
