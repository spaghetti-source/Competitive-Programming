// SPOJ 5: The Next Palindrome
// http://www.spoj.com/problems/PALIN/
//
// Solution: ad-hoc
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

using namespace std;

void carry_from(vector<int>& u, int k) {
  for (int j = k; u[j] >= 10; ++j) {
    if (j+1 >= u.size()) u.push_back(0);
    u[j+1] += 1;
    u[j] %= 10;
  }
}

int main() {
  int ncase; cin >> ncase;
  while (ncase--) {
    string s; cin >> s;
    vector<int> u;
    transform(s.rbegin(), s.rend(), 
        back_inserter(u), bind2nd(minus<char>(), '0'));
    u[0] += 1;
    carry_from(u, 0);
    int n = u.size();
    int m = n / 2;
    for (int i = 0; i < m; ++i) {
      if (u[i] > u[n-1-i]) {
        u[i+1] += 1;
        carry_from(u, i+1);
      }
      u[i] = u[n-1-i];
    }
    copy(u.begin(), u.end(), ostream_iterator<int>(cout));
    cout << endl;
  }
}

