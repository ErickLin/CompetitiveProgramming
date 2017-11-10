// 571A
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool is_triangle(vector<int> side_lens) {
  sort(side_lens.begin(), side_lens.end());
  return side_lens[0] + side_lens[1] > side_lens[2];
}

int largest_side_len(vector<int> side_lens) {
  return max(max(side_lens[0], side_lens[1]), side_lens[2]);
}

bool is_valid(int num) {
  return num >= -300000 && num <= 300000;
}

int main() {
  int a, b, c, l;
  cin >> a >> b >> c >> l;
  long long num_ways = 0;
  for (int d0 = 0; d0 <= l; d0++) {
    a += d0;
    for (int d1 = max(0, c - a - b + 1); d1 <= min(0, a - b + c - 1) + l - d0; d1++) {
      b += d1;
      pair<int, int> interval = make_pair(max(abs(a - b) + 1, c),
                                          min(a + b - 1, c + l - d0 - d1));
      if (interval.first <= interval.second) {
        num_ways += interval.second - interval.first + 1;
      }
      b -= d1;
    }
    a -= d0;
  }
  cout << num_ways << '\n';
}
