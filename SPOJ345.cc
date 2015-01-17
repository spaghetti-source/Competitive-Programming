// SPOJ 345: Mixtures
// http://www.spoj.com/problems/MIXTURES/
//
// Solution: dynamic programming (matrix chain multiplication)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>

using namespace std;

#define fst first
#define snd second
#define all(c) c.begin(), c.end()

int color[100],sum[100][100],memo[100][100];
int solve(int a, int b){
    if(b == a) return 0;
    if(b == a+1) return color[a] * color[b];
    int &ret = memo[a][b],aux;
    if(ret == -1){
        for(int i = a;i+1 <= b;++i){
            aux = sum[a][i] * sum[i+1][b] + solve(a,i) + solve(i+1,b);
            if(ret == -1 || aux < ret) ret = aux;
        }
    }
    return ret;
}


int main() {
  for (int n; scanf("%d", &n) == 1; ) {
    vector<int> a(n), b(n+1);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      b[i+1] = b[i] + a[i];
    }
    auto s = [&](int i, int j) { // a[i] + ... + a[j-1]
      return (b[j] - b[i]) % 100;
    };
    vector<vector<int>> T(n, vector<int>(n+1, 99999999));
    for (int i = 0; i < n; ++i) 
      T[i][i+1] = 0;
    for (int h = 2; h <= n; ++h) 
      for (int i = 0; i+h <= n; ++i) 
        for (int k = i+1; k < i+h; ++k) 
          T[i][i+h] = min(T[i][i+h], T[i][k] + T[k][i+h] + s(i,k) * s(k,i+h));
    printf("%d\n", T[0][n]);
  }
}
