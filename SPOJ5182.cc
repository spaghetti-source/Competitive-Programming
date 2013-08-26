// SPOJ 5182: Double Sorting
// http://www.spoj.com/problems/PAIRSORT/
//
// Solution: heuristic search (IDA*)
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cmath>
#include <cstring>
#include <functional>
#include <algorithm>
#include <queue>
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

#define ALL(c) c.begin(), c.end()
#define REP(i,n) for(int i=0;i<n;++i)
#define REPS(i,s,n) for(int i=s;i<n;++i)
#define fst first
#define snd second

typedef long long LL;
int N;

struct State {
  LL board; // 3bit-3bit  3bit-3bit  ...
  int cost;
  int get(int i, int a) {
    return (board >> (6*i + 3*a)) & 7;
  }
  void set(int i, int a, int x) {
    board &= ~((LL)7 << (6*i + 3*a));
    board |=  ((LL)x << (6*i + 3*a));
  }
  void normalize(int i) {
    if (get(i,0) > get(i,1)) {
      int x = get(i, 0);
      set(i, 0, get(i, 1));
      set(i, 1, x);
    }
  }
  void swap(int i, int a, int b) {
    int j = i+1, x = get(i, a), y = get(j, b);
    set(i, a, y); set(j, b, x);
    normalize(i); normalize(j);
  }
};

int lowerbound1(State s, int l, int r) {
  int t = 0;
  for (int i = l; i <= r; ++i)
    REP(a, 2) t += abs(s.get(i,a) - i);
  return s.cost + (t+1)/2;
}
int lowerbound2(State s, int l, int r) {
  int t = 0;
  for (int i = l; i <= r; ++i)
    for (int j = i+1; j <= r; ++j)
      REP(a, 2) REP(b, 2) 
        if      (s.get(i,a) == s.get(j,b)) t += 1;
        else if (s.get(i,a)  > s.get(j,b)) t += 2;
  for (int i = l; i <= r; ++i)
    if (s.get(i,0) != s.get(i,1)) ++t;
    else {
      bool ok = true;
      for (int j = l; j < i && ok; ++j)
        if (s.get(j,0) > i || s.get(j,1) > i) ok = 0;
      if (!ok) t += 2;
    }
  return s.cost + (t+5)/6;
}

unordered_set<LL> visited;
bool search(State s, int upperbound) {
  int l = 0, r = N-1;
  while (l  < N && s.get(l,0)==l && s.get(l,1)==l) ++l;
  while (r >= 0 && s.get(r,0)==r && s.get(r,1)==r) --r;
  if (l > r) return true;

  if (lowerbound1(s, l, r) > upperbound ||
      lowerbound2(s, l, r) > upperbound) return false;

  if (visited.count(s.board)) return false;
  visited.insert(s.board);

  for (int i = l; i < r; ++i) {
    int j = i+1, a = 1, b = 0;
    if (s.get(i,a) <= s.get(j, b)) continue;
    State t = s; t.cost += 1; t.swap(i,a,b);
    if (search(t, upperbound)) return true;
  }
  return false;
}
int IDAstar(State s) {
  int depth = 0;
  while (!search(s, ++depth)) 
    visited.clear();
  return depth;
}

int main() { 
  scanf("%d", &N);
  State s = { 0, 0 };
  REP(i, N) {
    LL a, b; scanf("%lld %lld", &a, &b); --a; --b;
    if (a > b) swap(a, b);
    s.board |= (a << (6*i+0));
    s.board |= (b << (6*i+3));
  }
  printf("%d\n", IDAstar(s));
}
