// 571A
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int a, b, c, l;
  cin >> a >> b >> c >> l;
  long long num_partitions_of_l = (long long) (l + 3) * (l + 2) * (l + 1) / 6;
  long long num_invalid_ways = 0;
  // Configurations can be invalid in three mutually exclusive ways:
  // (1) a + da >= b + db + c + dc => db + dc <= a + da - b - c
  // (2) b + db >= a + da + c + dc => db - dc >= a + da - b + c
  // (3) c + dc >= a + da + b + db => dc - db >= a + da + b - c
  // Also, db + dc <= l - da.
  // Assuming (1) WLOG, for each value of db + dc, there are db + dc + 1 ways
  // to partition db + dc as an integer sum. Thus, the number of invalid
  // configurations of type (1) is
  //   1 + 2 + ... + (x + 1) = (x + 1)(x + 2) / 2
  // where x = min{max(a + da - b - c, 0), l - da}.
  for (int da = 0; da <= l; da++) {
    if (a + da >= b + c) {
      int x = min(a + da - b - c, l - da);
      num_invalid_ways += (long long) (x + 1) * (x + 2) / 2;
    }
    /*
    // Proceeding using similar reasoning, the number of type (2) is
    //   1 + 2 + ... + (y + 1) = (y + 1)(y + 2) / 2
    // if y = l - (a + da - b + c) >= 0, and 0 otherwise.
    int y = l - (a + da - b + c);
    if (y >= 0) {
      num_invalid_ways += (long long) (y + 1) * (y + 2) / 2;
    }
    // Type (3) is symmetrical to type (2).
    int z = l - (a + da + b - c);
    if (z >= 0) {
      num_invalid_ways += (long long) (z + 1) * (z + 2) / 2;
    }
    */
  }
  // Repeat the above reasoning for cases (2) and (3).
  for (int db = 0; db <= l; db++) {
    if (b + db >= a + c) {
      int y = min(b + db - a - c, l - db);
      num_invalid_ways += (long long) (y + 1) * (y + 2) / 2;
    }
  }
  for (int dc = 0; dc <= l; dc++) {
    if (c + dc >= a + b) {
      int z = min(c + dc - a - b, l - dc);
      num_invalid_ways += (long long) (z + 1) * (z + 2) / 2;
    }
  }
  cout << num_partitions_of_l - num_invalid_ways << '\n';
}
