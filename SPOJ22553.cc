// SPOJ 22553: Stack Overflow
// http://www.spoj.com/problems/PRJAN15F/
//
// Solution: trivial

#include <iostream>
#include <vector>
#include <list>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

void doit() {
  int n, q;
  scanf("%d %d", &n, &q);

  vector<list<int>> piles(n+1);
  for (int i = 0; i < q; ++i) {
    char s[1024];
    scanf("%s", s);
    if (s[0] == 'p' && s[1] == 'u' && s[2] == 's') {
      int k, a;
      scanf("%d %d", &k, &a);
      piles[k].push_back(a);
    }
    if (s[0] == 'p' && s[1] == 'u' && s[2] == 't') {
      int k, l;
      scanf("%d %d", &k, &l); 
      piles[k].splice(piles[k].end(), piles[l]);
    }
    if (s[0] == 'p' && s[1] == 'o') {
      int k; 
      scanf("%d", &k);
      if (piles[k].empty()) {
        //printf("Empty!\n");
      } else {
        piles[k].pop_back();
      }
    }
    if (s[0] == 't' && s[1] == 'o') {
      int k; 
      scanf("%d", &k);
      if (piles[k].empty()) {
        printf("Empty!\n");
      } else {
        printf("%d\n", piles[k].back());
      }
    }
  }
}

int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    printf("Case %d:\n", icase+1);
    doit();
  }
}
