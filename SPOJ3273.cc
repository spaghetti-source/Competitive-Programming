// SPOJ 3273: Order statistic set
// http://www.spoj.com/problems/ORDERSET/
//
// Solution: coordinate compression & segment tree

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

struct segment_tree {
  int n;
  vector<int> x;
  segment_tree(int n) : n(n), x(4*n) { }
  void set(int i, int a, int l, int r, int k) {
    if (l + 1 == r) { x[k] = a; return; }
    int m = (l + r) / 2;
    if (i < m) set(i, a, l, m, 2*k+1);
    else       set(i, a, m, r, 2*k+2);
    x[k] = x[2*k+1] + x[2*k+2];
  }
  void insert(int i) { set(i, 1, 0, n, 0); }
  void erase(int i)  { set(i, 0, 0, n, 0); }

  int kth(int i, int l, int r, int k) {
    if (l + 1 == r) return l;
    int m = (l + r) / 2;
    if (i < x[2*k+1]) return kth(i, l, m, 2*k+1);
    else              return kth(i-x[2*k+1], m, r, 2*k+2);
  }
  int kth(int k) { return x[0] <= k ? -1 : kth(k, 0, n, 0); }
  int count(int i, int l, int r, int k) {
    if (l + 1 == r) return x[k];
    int m = (l + r) / 2;
    if (i < m) return count(i, l, m, 2*k+1);
    else       return x[2*k+1] + count(i, m, r, 2*k+2);
  }
  int count(int i) { return count(i, 0, n, 0); } 
};

vector<int> values;
unordered_map<int,int> compress;

int main() {
  int n; scanf("%d", &n);
  vector<pair<char, int>> ops(n);
  for (int i = 0; i < n; ++i) {
    char s[10];
    scanf("%s %d", s, &ops[i].snd);
    ops[i].fst = s[0];
    if (ops[i].fst == 'C')
      ops[i].snd -= 1;
    if (ops[i].fst != 'K') 
      values.push_back(ops[i].snd);
  }
  sort(all(values));
  values.erase(unique(all(values)), values.end());
  for (int i = 0; i < values.size(); ++i)
    compress[values[i]] = i;

  segment_tree T(values.size());

  for (auto &op: ops) {
    if (op.fst != 'K')
      op.snd = compress[op.snd];
    if (op.fst == 'I') {
      T.insert(op.snd);
    } else if (op.fst == 'D') {
      T.erase(op.snd);
    } else if (op.fst == 'K') {
      int a = T.kth(op.snd-1);
      if (a < 0) printf("invalid\n");
      else       printf("%d\n", values[a]);
    } else if (op.fst == 'C') {
      printf("%d\n", T.count(op.snd));
    }
  }
}
