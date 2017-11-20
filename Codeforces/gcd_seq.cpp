// 894C
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
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
  usi gcds;
  int smallest = 1000000, total_gcd = -1;
  forf(i, m) {
    int s;
    cin >> s;
    gcds.insert(s);
    smallest = min(smallest, s);
    total_gcd = (total_gcd == -1 ? s : gcd(total_gcd, s));
  }

  if (total_gcd != smallest) {
    cout << "-1\n";
    return 0;
  }

  vi ans;
  ans.push_back(smallest);
  for (int i : gcds) {
    if (i != smallest) {
      ans.push_back(i);
      ans.push_back(smallest);
    }
  }

  cout << ans.size() << '\n';
  cout << ans[0];
  for (int i = 1; i < ans.size(); i++) {
    cout << ' ' << ans[i];
  }
  cout << '\n';
}
