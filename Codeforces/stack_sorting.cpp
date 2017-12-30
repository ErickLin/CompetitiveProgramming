// 911E
#include <iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef vector<int> vi;

bool sortable(stack<int>& s) {
  if (s.size() <= 1) {
    return true;
  }
  int a = s.top();
  s.pop();
  int b = s.top();
  s.push(a);
  return a < b;
}

int main() {
  int n, k;
  cin >> n >> k;
  vi p(k);
  set<int> rem;
  forf3(i, n) {
    rem.insert(i);
  }
  stack<int> s;
  int cur_num = 1;
  forf(i, k) {
    cin >> p[i];
    rem.erase(p[i]);
    s.push(p[i]);
    while (!s.empty() && s.top() == cur_num) {
      s.pop();
      cur_num++;
    }
    if (!sortable(s)) {
      cout << "-1\n";
      return 0;
    }
  }
  cout << p[0];
  for (int i = 1; i < k; i++) {
    cout << ' ' << p[i];
  }
  sort(p.begin(), p.end());
  for (int elem : p) {
    for (int smaller = elem - 1; rem.count(smaller); smaller--) {
      cout << ' ' << smaller;
      rem.erase(smaller);
    }
  }
  for (auto it = rem.rbegin(); it != rem.rend(); it++) {
    cout << ' ' << *it;
  }
  cout << '\n';
}
