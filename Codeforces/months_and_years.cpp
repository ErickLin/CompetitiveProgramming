// 899B
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

int main() {
  int n;
  cin >> n;
  vi a(n);
  forf(i, n) {
    cin >> a[i];
  }
  forf(start_month, 12) {
    int idx = 0;
    bool leap_used = false;
    forf(i, 36) {
      int month = (start_month + i) % 12;
      bool matches = false;
      switch (month) {
        case 0:
          matches = (a[idx] == 31);
          break;
        case 1:
          matches = (a[idx] == 28 || a[idx] == 29);
          if (a[idx] == 29) {
            if (leap_used) {
              matches = false;
            } else {
              leap_used = true;
            }
          }
          break;
        case 2:
          matches = (a[idx] == 31);
          break;
        case 3:
          matches = (a[idx] == 30);
          break;
        case 4:
          matches = (a[idx] == 31);
          break;
        case 5:
          matches = (a[idx] == 30);
          break;
        case 6:
          matches = (a[idx] == 31);
          break;
        case 7:
          matches = (a[idx] == 31);
          break;
        case 8:
          matches = (a[idx] == 30);
          break;
        case 9:
          matches = (a[idx] == 31);
          break;
        case 10:
          matches = (a[idx] == 30);
          break;
        case 11:
        default:
          matches = (a[idx] == 31);
      }
      if (matches) {
        if (++idx == n) {
          cout << "YES\n";
          return 0;
        }
      } else {
        idx = 0;
      }
    }
  }
  cout << "NO\n";
}
