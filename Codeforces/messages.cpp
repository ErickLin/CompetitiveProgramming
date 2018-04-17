// 964B
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<int> vi;

int main() {
  int n, A, B, C, T; cin >> n >> A >> B >> C >> T;
  ll max_sum = 0;
  vi t(n);
  forf(i, n) {
    cin >> t[i];
    max_sum += A;
    if (C > B) {
      max_sum += (C - B) * (T - t[i]);
    }
  }
  cout << max_sum << '\n';
}
