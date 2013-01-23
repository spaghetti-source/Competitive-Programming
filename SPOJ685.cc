// SPOJ 685: Partition the sequence
// http://www.spoj.com/problems/SEQPAR/
//
// Solution: binary search + DP with binary search tree
//
// 1. Do binary search to convert minimization problem
//    to feasibility problem.
//
// 2. To solve the feasibility problem, we use the following fact:
//      Let f = min #parts of M partition,
//          g = max #parts of M partition.
//      Then, for all k : f <= k <= g, 
//      there exist a k parts M partition.
//
// 3. Computation of f and g:
//    The DP relation is 
//       f(i) = max f(j)+1 | a[j,i) <= M
//    This can be solved in O(n log n) times,
//    using binary search tree of key = a[0]+...+a[k]
//    and value = f(k).

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

#include <ctime>

using namespace std;
const int INF = 1 << 30;

struct RangeMinimumQuery {
  typedef int Key;
  typedef pair<int,int> Value;
  struct Node {
    Key key;
    Value value, sum;
    int pr;
    Node *ch[2];
    Node(Key key, Value value) : 
      key(key), value(value), pr(rand()) { ch[0] = ch[1] = 0; }
  } *root;
  RangeMinimumQuery() : root(0) { }

  Value SUM(Node *n) { return n ? n->sum : Value(INF,-INF); }
  Value PLUS(Value x, Value y) {
    return Value(min(x.first, y.first), max(x.second, y.second)); 
  }
  Node *update(Node *n) {
    if (n) n->sum = PLUS(n->value, PLUS(SUM(n->ch[0]), SUM(n->ch[1])));
    return n;
  }
  Node *rotate(Node *n, int b) {
    Node *m = n->ch[b];
    n->ch[b] = m->ch[!b];
    m->ch[!b] = update(n);
    return update(m);
  }
  Node *insert(Node *n, Key key, Value value) {
    if (!n) return update(new Node(key, value));
    int b = (n->key < key); 
    n->ch[b] = insert(n->ch[b], key, value);
    return n->ch[b]->pr < n->pr ? rotate(n, b) : update(n);
  }
  void insert(Key key, Value value) {
    root = insert(root, key, value);
  }
  Value rangeSum(Node *n, Key key) { // sum over n.key >= key
    if (!n) return SUM(n);
    if (n->key < key) return rangeSum(n->ch[1], key);
    return PLUS(rangeSum(n->ch[0], key), PLUS(n->value, SUM(n->ch[1])));
  }
};

int a[20000], s[20000], n, k;
bool possible(int m) {
  pair<int,int> p;
  RangeMinimumQuery RMQ;
  RMQ.insert(0, make_pair(0, 0));
  for (int i = 0; i < n; ++i) {
    p = RMQ.rangeSum(RMQ.root, s[i] - m);
    p.first += 1; p.second += 1;
    RMQ.insert(s[i], p);
  }
  return p.first <= k && k <= p.second;
}
int solve() {
  int l = -INF, r = +INF;
  while (l+1 < r) { 
    int m = (r + l) / 2;
    if (possible(m)) r = m;
    else l = m;
  }
  return r;
}
int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) 
      scanf("%d", &a[i]);
    s[0] = a[0];
    for (int i = 1; i < n; ++i)
      s[i] = s[i-1] + a[i];
    printf("%d\n", solve());
  }
}
