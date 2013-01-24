// SPOJ 13381: Manku Word
// http://www.spoj.com/problems/MAY99_2/
//
// Solution: Ad-hoc (k'th alphabetical word)

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long LL;

void kthWord(LL k) {
  vector<char> s;
  for (; k > 0; k = (k - 1) / 5) 
    s.push_back( "manku"[(k - 1) % 5] );
  for (int i = s.size()-1; i >= 0; --i)
    printf("%c", s[i]);
  printf("\n");
}
int main() {
  int t; scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    LL n; scanf("%lld", &n);
    kthWord(n);
  }
}
