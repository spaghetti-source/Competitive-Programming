// SPOJ 4172: Multiplicative digital root
// http://www.spoj.com/problems/DROOT/
//
// Solution: big integer (fast power)
//
// Note: remove redundant spaces for source limit

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <cstring>
using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
typedef long long ll;
struct bigint {
  /*static const ll B = 1000000000, logB = 9;*/ 
  static const ll B = 10000, logB = 4;
  vector<ll> buf;
  bigint &normalize() { 
    ll c = 0;
    for (int i = 0; i < buf.size(); ++i) {
      buf[i] += c; 
      c = buf[i] / B;
      buf[i] %= B;
    }
    if (c > 0) buf.push_back(c);
    return *this; 
  }
  bigint(char s[]) {
    int n = strlen(s);
    for (int i = n; i >= 1; i -= logB) {
      ll c = 0, b = 1;
      for (int j = i-1; j >= max(0, i-(int)logB); --j) {
        c += b * (s[j] - '0');
        b *= 10; }
      buf.push_back(c);
    }
  }
  bigint(ll c) {
    buf.push_back(c);
    normalize();
  }
  bigint &operator*=(const bigint &y) {
    vector<ll> tmp(buf.size()+y.buf.size()-1);
    for (int i = 0; i < buf.size(); ++i) 
      for (int j = 0; j < y.buf.size(); ++j) 
        tmp[i+j] += buf[i] * y.buf[j];
    buf.swap(tmp);
    return normalize();
  }
  bigint &operator*=(ll y) {
    for (int i = 0; i < buf.size(); ++i) 
      buf[i] *= y;
    return normalize();
  }
};
bigint operator*(bigint x, const bigint &y) {
  return x *= y;
}

bigint operator*(bigint x, ll y) {
  return x * y;
}
bigint pow(bigint a, ll e) {
  bigint x = bigint(1);
  for (; e > 0; e >>= 1) {
    if (e & 1) x = x * a; a = a * a; }
  return x;
}
ostream &operator<<(ostream &os, const bigint &x) {
  os << x.buf.back();
  for (int i = x.buf.size()-2; i >= 0; --i)
    os << setfill('0') << setw(x.logB) << x.buf[i];
  return os;
}
int main() {
  int ncase;
  scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    char s[10010];
    scanf("%s", s); bigint x(s);
    while (x.buf.size() > 1 || x.buf[0] >= 10) {
      unordered_map<int, int> count;
      for (int i = 0; i < x.buf.size(); ++i) {
        ll a = x.buf[i];
        while (a > 0) {
          ll c = a % 10;
          for (int i = 2; i <= c; ++i) {
            while (c % i == 0) {
              ++count[i];
              c /= i;
            }
          }
          a /= 10;
        }
      }
      x = bigint(1);
      for (auto p: count) x = x * pow(bigint(p.fst), p.snd);
    }
    cout << x << endl;
  }
}

