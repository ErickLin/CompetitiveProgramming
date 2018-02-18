// 915C
#include <iostream>
#include <map>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

int main() {
  string a, b;
  cin >> a >> b;
  if (a.size() < b.size()) {
    sort(a.begin(), a.end(), greater<char>());
    cout << a << '\n';
  } else {
    map<char, int> occ;
    for (char dig : a) {
      occ[dig]++;
    }
    string c;
    forf(i, a.size()) {
      if (occ[b[i]] > 0) {
        c += b[i];
        occ[b[i]]--;
      } else {
        int j = i;
        char smaller_dig = b[j] - 1;
        while (smaller_dig >= '0' && occ[smaller_dig] == 0) {
          smaller_dig--;
        }
        for (j = i - 1; j >= 0 && smaller_dig < '0'; j--) {
          occ[c[j]]++;
          c.erase(j);
          char smaller_dig = b[j] - 1;
          while (smaller_dig >= '0' && occ[smaller_dig] == 0) {
            smaller_dig--;
          }
        }
        c += smaller_dig;
        occ[smaller_dig]--;
        for (const auto& kv : occ) {
          forf(j, kv.second) {
            c += kv.first;
          }
        }
        sort(c.begin() + j + 1, c.end(), greater<char>());
        break;
      }
    }
    cout << c << '\n';
  }
}
