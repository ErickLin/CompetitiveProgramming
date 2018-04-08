#include <iostream>
using namespace std;
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;

ll tot_damage(string& p) {
  ll ret = 0;
  int power = 1;
  for (char c : p) {
    if (c == 'C') {
      power *= 2;
    } else {
      ret += power;
    }
  }
  return ret;
}

int last_pos_s_after_c(string& p) {
  forb(i, p.size()) {
    if (i && p[i - 1] == 'C' && p[i] == 'S') {
      return i;
    }
  }
  return -1;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cout << "Case #" << t << ": ";
    int d;
    string p;
    cin >> d >> p;
    if (tot_damage(p) <= d) {
      cout << "0\n";
      continue;
    }

    bool found = false;
    int num_swaps = 0;
    int swap_pos;
    while ((swap_pos = last_pos_s_after_c(p)) != -1) {
      num_swaps++;
      char temp = p[swap_pos - 1];
      p[swap_pos - 1] = p[swap_pos];
      p[swap_pos] = temp;
      if (tot_damage(p) <= d) {
        found = true;
        cout << num_swaps << '\n';
        break;
      }
    }
    if (!found) {
      cout << "IMPOSSIBLE\n";
    }
  }
}
