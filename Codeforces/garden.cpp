// 915A
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

int main() {
  int n, k;
  cin >> n >> k;
  vi a(n);
  int min_hours = INT_MAX;
  forf(i, n) {
    cin >> a[i];
    if (k % a[i] == 0) {
      min_hours = min(min_hours, k / a[i]);
    }
  }
  cout << min_hours << '\n';
}
