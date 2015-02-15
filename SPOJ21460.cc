// SPOJ 21460: Tresi and Girls
// http://www.spoj.com/problems/NPC2014E/
//
// Solution: ad-hoc; exhaustive by hand
//
// hard problem :(
//

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

bool happy(vector<int> x) {
  if (x[1] == 0 && x[2] == 0) return true;
  return false;
}

int solve(vector<int> x) {
  int cost = 0;
  if (x[2] >= x[1]) { // (1,2) ==> (0,3)
    cost += x[1];
    x[3] += x[1];
    x[2] -= x[1];
    x[1]  = 0;
    if (x[2] >= 3) { // (2,2,2) ==> (3,3,0)
      cost += 2 * (x[2] / 3);
      x[3] += 2 * (x[2] / 3);
      x[2] %= 3;
    }
    cost += 2 * (x[2] / 2); // (2,2) ==> (4,0)
    x[2] %= 2;
    if (x[2] == 1) {
      if      (x[4] >= 1) cost += 1; // (2,4)   ==> (3,3)
      else if (x[3] >= 2) cost += 2; // (2,3,3) ==> (0,4,4)
      else                cost = -1; 
    }
  } else { // 
    cost += x[2]; // (2,1) ==> (3,0)
    x[3] += x[2];
    x[1] -= x[2];
    x[2]  = 0;
    cost += 2 * (x[1] / 3); // (1,1,1) ==> (3,0,0)
    x[3] += x[1] / 3;
    x[1] %= 3; 
    if (x[1] == 1) {
      if      (x[3] >= 1) cost += 1; // (1,3) ==> (0,4)
      else if (x[4] >= 2) cost += 2; // (1,4,4) ==> (3,3,3)
      else                cost = -1;
    } else if (x[1] == 2) {
      if      (x[4] >= 1) cost += 2; // (1,1,4) ==> (0,3,3)
      else if (x[3] >= 2) cost += 2; // (1,1,3,3) ==> (0,0,4,4)
      else                cost = -1;
    }
  }
  return cost;
}

int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    int n; scanf("%d", &n);
    vector<int> x(5);
    for (int i = 0; i < n; ++i) {
      int a; scanf("%d", &a);
      ++x[a];
    }
    int ans = solve(x);
    if (ans >= 0) printf("%d\n", ans);
    else          printf("Tresi gagal memuaskan gadisnya.\n");
  }
}
