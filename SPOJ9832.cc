// SPOJ 9832: Matrix Inverse
// http://www.spoj.com/problems/MIFF/
//
// Solution: modular arithmetics

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef int ll;
typedef vector<ll> vec;
typedef vector<vec> mat;


ll sub(ll a, ll b, ll M) { 
  while (a < b) a += M;
  return a - b;
}
ll add(ll a, ll b, ll M) {
  a += b;
  while (a >= M) a -= M;
  return a;
}
ll mul(ll a, ll b, ll M) {
  ll r = a*b - ll(double(a)*b/M + 0.5)*M;
  while (r < 0) r += M;
  return r;
}
ll div(ll a, ll b, ll M) {
  ll u = 1, x = 0, s = b, t = M;
  while (s) {
    ll q = t / s;
    swap(x -= u * q, u);
    swap(t -= s * q, s);
  }
  if (a % t) return -1;
  return mul(x < 0 ? x + M : x, a / t, M);
}

mat inverse(mat A, ll M) {
  int n = A.size();
  mat B(n, vec(n));
  for (int i = 0; i < n; ++i) 
    B[i][i] = 1;

  for (int i = 0; i < n; ++i) {

    int j = i; // partial pivotting
    while (j < n && A[j][i] == 0) ++j;
    if (j == n) return {};
    swap(A[i], A[j]); 
    swap(B[i], B[j]);

    ll inv = div(1, A[i][i], M);
    for (int k = i; k < n; ++k)
      A[i][k] = mul(A[i][k], inv, M);
    for (int k = 0; k < n; ++k)
      B[i][k] = mul(B[i][k], inv, M);
    for (int j = 0; j < n; ++j) {
      if (i == j || A[j][i] == 0) continue;
      ll cor = A[j][i];
      for (int k = i; k < n; ++k)
        A[j][k] = sub(A[j][k], mul(cor, A[i][k], M), M);
      for (int k = 0; k < n; ++k)
        B[j][k] = sub(B[j][k], mul(cor, B[i][k], M), M);
    }
  }
  return B;
}


int main() {
  for (int icase = 0; ; ++icase) {
    int n, p; scanf("%d %d", &n, &p);
    if (n == 0 && p == 0) break;

    if (icase > 0) printf("\n");

    mat A(n, vec(n));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        scanf("%d", &A[i][j]);

    mat B = inverse(A, p);
    if (!B.empty()) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          printf("%d ", B[i][j]);
        }
        printf("\n");
      }
    } else {
      printf("singular\n");
    }
  }
}

