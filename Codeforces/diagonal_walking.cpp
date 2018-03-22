// 954A
#include <iostream>
#include <stack>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

int main() {
  int n; cin >> n;
  stack<char> stk;
  forf(i, n) {
    char c; cin >> c;
    if (!stk.empty() && ((stk.top() == 'U' && c == 'R') || (stk.top() == 'R' && c == 'U'))) {
      stk.pop();
      stk.push('D');
    } else {
      stk.push(c);
    }
  }
  cout << stk.size() << '\n';
}
