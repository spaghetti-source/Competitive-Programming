// SPOJ 8001: Fibonacci Sum
// http://www.spoj.com/problems/FIBOSUM
//
// Algorithm: Math (matrix power)
//
// A standard Fibonacci: 
//   f(n) = [ fib(n+1) fib(n) ] then
//   f(n) = |1 1| f(n-1) = A^n f(0)
//          |1 0|
//
// Extension to the sum:
//   f(n) = [fib(n+1), fib(n), sum(n+1)] where sum(n) := fib[0,n)
// Then
//   f(n) = |1 1 0| f(n-1) = A^n f(0)
//          |1 0 0|
//          |1 0 1|
//
// In general, |A 0|^n = |A^n 0|
//             |b 1|     |S_n 1|
// where S_n = b (I + A + A^2 + ... + A^{n-1})

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)
#define fst first
#define snd second

typedef long long LL;
typedef vector<LL> Vector;
typedef vector<Vector> Matrix;

LL addMod(LL a, LL b, LL M) {
  return (a += b) < M ? a : a - M;
}
LL subMod(LL a, LL b, LL M) { 
  return a >= b ? a - b : (a + M) - b; 
}
LL mulMod(LL a, LL b, LL M) {
  LL x = 0;
  for (; b > 0; b >>= 1) {
    if (b & 1) x = addMod(x, a, M);
    a = addMod(a, a, M);
  }
  return x;
}

Matrix eye(int n) {
  Matrix I(n, Vector(n));
  REP(i, n) I[i][i] = 1;
  return I;
}
Matrix mulMod(Matrix A, Matrix B, LL M) {
  int l = A.size(), m = B.size(),  n = B[0].size();
  Matrix C(l, Vector(n));
  REP(i,l) REP(k,m) REP(j,n) 
    C[i][j] = addMod(C[i][j], mulMod(A[i][k], B[k][j], M), M);
  return C;
}
Matrix powMod(Matrix A, LL b, LL M) {
  Matrix X = eye(A.size());
  for (; b > 0; b >>= 1) {
    if (b & 1) X = mulMod(X, A, M);
    A = mulMod(A, A, M);
  }
  return X;
}

void disp(Matrix A) {
  cout << "[";
  REP(i, A.size()) {
    if (i != 0) cout << " ";
    REP(j, A[i].size()) {
      cout << A[i][j];
      if (j != A[i].size()-1) cout << ", ";
      else                    cout << "; ";
    }
    cout << endl;
  }
  cout << endl;
}

Matrix A;
LL fibosum(LL n, LL m) {
  if (n < m) swap(n, m);
  const LL p = 1000000007;
  Matrix An = powMod(A, n,  p);
  Matrix Am = powMod(A, m-1,p);
  return subMod(An[2][0], Am[2][0], p);
}

int main() {
  A = Matrix(3, Vector(3));
  A[0][0] = A[0][1] = A[1][0] = A[2][0] = A[2][2] = 1;
  int T; scanf("%d", &T);
  while (T--) {
    LL n, m; scanf("%lld %lld", &n, &m);
    printf("%lld\n", fibosum(n, m));
  }
}
