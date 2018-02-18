// 932A
#include <iostream>
using namespace std;
#define forb(i, n) for (int i = n - 1; i >= 0; i--)

int main() {
  string a;
  cin >> a;
  int n = a.size();
  forb(i, n - 1) {
    a += a[i];
  }
  cout << a << '\n';
}
