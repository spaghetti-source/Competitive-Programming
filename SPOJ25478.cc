// SPOJ 25478: Hugo's Homework
// http://www.spoj.com/problems/TAP2015H/
//
// Solution: trivial

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

int main() {
  for (char s[1024]; ~scanf("%s", s); ) {
    vector<int> a;
    for (int i = 0; s[i]; ++i)
      a.push_back(s[i] - '0');
    reverse(all(a));

    int step = 0;
    while (!a.empty()) {
      ++step;
      vector<int> b = a;
      sort(all(b)); reverse(all(b));
      for (int i = 0; i < a.size(); ++i)
        if ((a[i] -= b[i]) < 0) { a[i] += 10; a[i+1] -= 1; }
      while (!a.empty() && !a.back()) a.pop_back();
    }
    printf("%d\n", step);
  }
}
