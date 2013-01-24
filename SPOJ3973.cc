// SPOJ 3973: 0 0 Pairs
// http://www.spoj.com/problems/M00PAIR/
//
// Solution: Math, Big Integer
//
// next   current
// #00  = #01
// #01  = #00 + #1
//
// --> #00 = #00'' + #1

#include <cstdio>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;
struct BigInt {
  static const LL B = 10000000;
  static const int N = 1000, BW = 7;
  LL x[N+1];
  BigInt normalize() {
    for (int i = 0; i < N; ++i) {
      x[i+1] += x[i] / B;
      x[i] %= B;
    }
    return *this;
  }
  BigInt(LL t) { 
    memset(x, 0, sizeof(x));
    x[0] = t;
    normalize();
  }
  BigInt operator+(BigInt y) {
    for (int i = 0; i < N; ++i) 
      x[i] += y.x[i];
    return normalize();
  }
  BigInt operator*(BigInt y) {
    BigInt z(0);
    for (int i = 0; i < N; ++i) 
      for (int j = 0; i+j < N; ++j) 
        z.x[i+j] += x[i] * y.x[j];
    return z.normalize();
  }
}; 

void set_string(char dst[], BigInt x) {
  char buf[256];
  int i = BigInt::N - 1;
  while (i > 0 && x.x[i] == 0) --i;
  sprintf(buf, "%d", x.x[i--]); 
  strcpy(dst, buf);
  while (i >= 0) {
    sprintf(buf, "%0*d", BigInt::BW, x.x[i--]);
    strcat(dst, buf);
  }
}
char solution[1000][1000];
int main() {
  BigInt f(1), g(1), h(2);
  strcpy(solution[1], "0");
  strcpy(solution[2], "1");
  for (int i = 3; i < 1000; ++i) {
    swap(f = f + h, g);
    h = h + h;
    set_string(solution[i], f);
  }
  int n; 
  while (scanf("%d", &n) == 1) {
    printf("%s\n", solution[n]);
  }
}
