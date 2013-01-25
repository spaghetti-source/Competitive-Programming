// SPOJ 5132: Hello Kitty
// http://www.spoj.com/problems/HELLOKIT/
//
// Solution: String, Ad-Hoc
//
// Remark. This is an ambiguous problem.
// For the input 'abab 1', I cannot decide
// which is the collect output:
//   abab
//   baba
// or 
//   abab
//   baba
//   abab <- same as first line
//   baba
//
// Following code produce the later output.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

void solve(string s, int k) {
  int n = s.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) 
      cout << s.substr(i,n-i) << s.substr(0,i);
    cout << endl;
  }
}

int main() {
  string s;
  int k; 
  while (cin >> s >> k && s[0] != '.')
    solve(s, k);
}
