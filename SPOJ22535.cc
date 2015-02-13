// SPOJ 22535: String Play
// http://www.spoj.com/problems/PRJAN15C/
//
// Solution: 

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef long long ll;
/*
ll naive(string s) {
  int n = s.size();
  unordered_set<string> S;
  for (int i = 1; i <= n; ++i)  // s[0,i) ++ s[n-j,n)
    for (int j = 1; j <= n; ++j) 
      S.insert( s.substr(0,i) + s.substr(n-j, j) );
  return S.size();
}
*/
ll solve(char s[]) {
  ll n = strlen(s);
  unordered_map<char, ll> count;
  for (int i = 0; s[i]; ++i) ++count[s[i]];
  ll ans = 0;
  for (int i = 0; s[i]; ++i) {
    ans += n - count[s[i+1]];
    if (s[n-1] == s[i+1]) ++ans;
  }
  return ans;
}

char s[10000010]; 
int main() {
  for (; ~scanf("%s", s); ) {
    printf("%lld\n", solve(s));
  }
}

