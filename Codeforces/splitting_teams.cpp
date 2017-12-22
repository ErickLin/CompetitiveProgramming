// 899A
#include <iostream>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

int main() {
  int n;
  cin >> n;
  int num1 = 0, num2 = 0;
  forf(i, n) {
    int num;
    cin >> num;
    if (num == 1) {
      num1++;
    } else {
      num2++;
    }
  }
  int ans = 0;
  int d = min(num1, num2);
  ans += d;
  num1 -= d;
  num2 -= d;
  ans += num1 / 3;
  cout << ans << '\n';
}
