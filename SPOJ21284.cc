// SPOJ 21284: Can You make It Empty 3
// http://www.spoj.com/problems/EMTY3/
//
// Solution: greedy

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int solve(char s[]) {
  int n = strlen(s);
  vector<pair<char,int>> x;
  x.push_back({'_', -1});
  vector<int> f(n+1);
  int r = 0;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    x.push_back({s[i], i});
    while (x.size() >= 3 && x[x.size()-3].fst == '1' && x[x.size()-2].fst == '0' && x[x.size()-1].fst == '0') {
      x.pop_back();
      x.pop_back();
      x.pop_back();
    }
    f[i] = x.back().snd;
    ans = max(ans, i - f[i]);
    /*
    cout << i << ": ";
    for (int j =0; j < x.size(); ++j) {
      cout << "(" << x[j].fst << "," << x[j].snd << ")";
    }
    cout << endl;
    */
  }
  return ans;
}


int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    char s[200010];
    scanf("%s", s);
    printf("Case %d: %d\n", icase+1, solve(s));
  }
}
