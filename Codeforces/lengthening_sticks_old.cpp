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
  vector<int> nums(3);
  int l;
  cin >> nums[0] >> nums[1] >> nums[2] >> l;
  long long num_ways = 0;
  for (int d0 = 0; d0 <= l; d0++) {
    nums[0] += d0;

    vector<int> d1(2);
    d1[0] = 9999999;
    d1[1] = -9999999;
    int lo = 0, hi = l - d0;
    // Find the smallest d1 such that a + d0, b + d1, c form a triangle
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      nums[1] += mid;
      if (is_triangle(nums)) {
        hi = mid - 1;
        if (mid < d1[0]) {
          d1[0] = mid;
        }
      } else {
        if (nums[1] == largest_side_len(nums)) {
          hi = mid - 1;
        } else {
          lo = mid + 1;
        }
      }
      nums[1] -= mid;
    }
    lo = 0;
    hi = l - d0;
    // Find the largest d1 such that a + d0, b + d1, c form a triangle
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      nums[1] += mid;
      if (is_triangle(nums)) {
        lo = mid + 1;
        if (mid > d1[1]) {
          d1[1] = mid;
        }
      } else {
        if (nums[1] == largest_side_len(nums)) {
          hi = mid - 1;
        } else {
          lo = mid + 1;
        }
      }
      nums[1] -= mid;
    }

    vector<vector<int> > d2(2, vector<int>(2));
    for (int d1_i = 0; d1_i <= 1; d1_i++) {
      d2[d1_i][0] = 9999999;
      d2[d1_i][1] = -9999999;
    }
    for (int d1_i = 0; d1_i <= 1; d1_i++) {
      nums[1] += d1[d1_i];

      lo = 0;
      hi = l - d0 - d1[d1_i];
      // Find the smallest d2 such that a + d0, b + d1[d1_i], c + d2 form a triangle
      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        nums[2] += mid;
        if (is_triangle(nums)) {
          hi = mid - 1;
          if (mid < d2[d1_i][0]) {
            d2[d1_i][0] = mid;
          }
        } else {
          if (nums[2] == largest_side_len(nums)) {
            hi = mid - 1;
          } else {
            lo = mid + 1;
          }
        }
        nums[2] -= mid;
      }
      lo = 0;
      hi = l - d0 - d1[d1_i];
      // Find the largest d2 such that a + d0, b + d1[d1_i], c + d2 form a triangle
      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        nums[2] += mid;
        if (is_triangle(nums)) {
          lo = mid + 1;
          if (mid > d2[d1_i][1]) {
            d2[d1_i][1] = mid;
          }
        } else {
          if (nums[2] == largest_side_len(nums)) {
            hi = mid - 1;
          } else {
            lo = mid + 1;
          }
        }
        nums[2] -= mid;
      }

      nums[1] -= d1[0];
    }

    nums[0] -= d0;

    if (is_valid(d2[0][0]) && is_valid(d2[0][1]) && is_valid(d2[1][0]) && is_valid(d2[1][1])) {
      int a = d2[0][1] - d2[0][0] + 1;
      int b = d2[1][1] - d2[1][0] + 1;
      num_ways += (a + b) * (abs(b - a) + 1) / 2;
      if ((b - a) % 2 == 0) {
        num_ways += (a + b) / 2;
      }
    }
  }
  cout << num_ways << '\n';
}
