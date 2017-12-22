// 899C
#include <iostream>
#include <vector>
using namespace std;
#define pb push_back
typedef long long ll;
typedef vector<int> vi;

int main() {
  int n;
  cin >> n;
  int group1_size = (ll) n * (n + 1) / 2;
  if (group1_size % 2 == 0) {
    cout << "0\n";
  } else {
    cout << "1\n";
  }
  vi group1;
  int sum_remaining = group1_size / 2, highest_left = n;
  while (highest_left < sum_remaining) {
    sum_remaining -= highest_left;
    group1.pb(highest_left);
    highest_left--;
  }
  group1.pb(sum_remaining);
  cout << group1.size();
  for (int elem : group1) {
    cout << ' ' << elem;
  }
  cout << '\n';
}
