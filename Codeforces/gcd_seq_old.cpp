// 894C
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef vector<int> vi;
typedef unordered_set<int> usi;

int gcd(int a, int b) {
  if (max(a, b) % min(a, b) == 0) {
    return min(a, b);
  }
  return gcd(min(a, b), max(a, b) % min(a, b));
}

int main() {
  int m;
  cin >> m;
  set<int, greater<int>> gcds;
  forf(i, m) {
    int s;
    cin >> s;
    gcds.insert(s);
  }
  vi ans;
  bool possible = true;
  usi taken;
  while (taken.size() < gcds.size()) {
    possible = false;
    for (int s : gcds) {
      if (taken.count(s)) {
        continue;
      }
      possible = true;
      int running_gcd = s;
      forb(i, ans.size()) {
        running_gcd = gcd(running_gcd, ans[i]);
        if (!gcds.count(running_gcd)) {
          possible = false;
        }
      }
      if (!possible) {
        continue;
      }
      ans.push_back(s);
      taken.insert(s);
      running_gcd = s;
      forb(i, ans.size()) {
        running_gcd = gcd(running_gcd, ans[i]);
        taken.insert(running_gcd);
      }
    }
    if (!possible) {
      break;
    }
  }
  if (possible) {
    cout << ans.size() << '\n';
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++) {
      cout << ' ' << ans[i];
    }
    cout << '\n';
  } else {
    cout << "-1\n";
  }
}
