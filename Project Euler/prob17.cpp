#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> a(1001);
  a[0] = 4;
  a[1] = 3;
  a[2] = 3;
  a[3] = 5;
  a[4] = 4;
  a[5] = 4;
  a[6] = 3;
  a[7] = 5;
  a[8] = 5;
  a[9] = 4;
  a[10] = 3;
  a[11] = 6;
  a[12] = 6;
  a[13] = 8;
  a[14] = 8;
  a[15] = 7;
  a[16] = 7;
  a[17] = 9;
  a[18] = 8;
  a[19] = 8;
  a[20] = 6;
  a[30] = 6;
  a[40] = 5;
  a[50] = 5;
  a[60] = 5;
  a[70] = 7;
  a[80] = 6;
  a[90] = 6;
  for (int i = 20; i <= 90; i += 10) {
    for (int j = 1; j <= 9; j++) {
      a[i + j] = a[i] + a[j];
    }
  }
  for (int i = 100; i <= 900; i += 100) {
    a[i] = a[i / 100] + 7;
    for (int j = 1; j <= 99; j++) {
      a[i + j] = a[i] + 3 + a[j];
    }
  }
  a[1000] = a[1] + 8;
  cout << a[342] << ' ' << a[115] << '\n';
  int sum = 0;
  for (int i = 1; i <= 1000; i++) {
    sum += a[i];
  }
  cout << sum << '\n';
}
