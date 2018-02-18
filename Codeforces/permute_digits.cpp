// 915C
#include <iostream>
#include <map>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

string recurse(string c, map<char, int> a_occs, string& b, int pos,
               bool used_smaller) {
  if (pos == b.size()) {
    return c;
  }
  if (used_smaller) {
    for (const auto& kv : a_occs) {
      forf(i, kv.second) {
        c += kv.first;
      }
    }
    sort(c.begin() + pos, c.end(), greater<char>());
    return c;
  }
  if (a_occs[b[pos]] > 0) {
    c += b[pos];
    a_occs[b[pos]]--;
    string res = recurse(c, a_occs, b, pos + 1, false);
    if (!res.empty()) {
      return res;
    }
    c.erase(pos);
    a_occs[b[pos]]++;
  }
  if (b[pos] > '0') {
    for (char smaller_dig = b[pos] - 1; smaller_dig >= '0'; smaller_dig--) {
      if (a_occs[smaller_dig] > 0) {
        c += smaller_dig;
        a_occs[smaller_dig]--;
        return recurse(c, a_occs, b, pos + 1, true);
      }
    }
  }
  return "";
}

int main() {
  string a, b;
  cin >> a >> b;
  if (a.size() < b.size()) {
    sort(a.begin(), a.end(), greater<char>());
    cout << a << '\n';
  } else {
    map<char, int> a_occs;
    for (char dig : a) {
      a_occs[dig]++;
    }
    cout << recurse("", a_occs, b, 0, false) << '\n';
  }
}
