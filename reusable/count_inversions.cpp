#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

template<typename T>
ll count_inversions(vector<T> &arr) {
  if (arr.size() >= 2) {
    vector<T> left(arr.size() >> 1);
    for (int i = 0; i < (arr.size() >> 1); i++) {
      left[i] = arr[i];
    }
    vector<T> right(arr.size() - (arr.size() >> 1));
    for (int i = (arr.size() >> 1); i < arr.size(); i++) {
      right[i - (arr.size() >> 1)] = arr[i];
    }
    ll inversions = count_inversions(left) + count_inversions(right);
    int i = 0;
    int j = 0;
    while (i + j < arr.size()) {
      if (j == right.size() || (i < left.size() && left[i] <= right[j])) {
        arr[i + j] = left[i++];
      } else {
        arr[i + j] = right[j++];
        inversions += left.size() - i;
      }
    }
    return inversions;
  }
  return 0;
}
