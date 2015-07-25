#include <iostream>
using namespace std;

int main() {
  int day = (1 + 365) % 7;
  int count = (day % 7 == 0 ? 1 : 0);
  for (int year = 1; year <= 100; year++) {
    for (int month = 1; month <= 12; month++) {
      if (month == 2) {
        day = (day + (year % 4 == 0 ? 29 : 28)) % 7;
      } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        day = (day + 30) % 7;
      } else {
        day = (day + 31) % 7;
      }
      if (day % 7 == 0) {
        count++;
      }
    }
  }
  cout << count << '\n';
}
