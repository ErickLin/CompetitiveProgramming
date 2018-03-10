// 948A
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<char> vc;
typedef vector<vc> vvc;

bool next_to_sheep(int i, int j, vvc& pasture) {
  int r = pasture.size(), c = pasture[0].size();
  if (i > 0 && pasture[i - 1][j] == 'S') {
    return true;
  }
  if (j > 0 && pasture[i][j - 1] == 'S') {
    return true;
  }
  if (i < r - 1 && pasture[i + 1][j] == 'S') {
    return true;
  }
  if (j < c - 1 && pasture[i][j + 1] == 'S') {
    return true;
  }
  return false;
}

int main() {
  int r, c;
  cin >> r >> c;
  vvc pasture(r, vc(c));
  forf(i, r) {
    forf(j, c) {
      cin >> pasture[i][j];
    }
  }

  forf(i, r) {
    forf(j, c) {
      if (pasture[i][j] == 'W' && next_to_sheep(i, j, pasture)) {
        cout << "No\n";
        return 0;
      }
    }
  }

  cout << "Yes\n";
  forf(i, r) {
    forf(j, c) {
      if (pasture[i][j] == '.') {
        cout << 'D';
      } else {
        cout << pasture[i][j];
      }
    }
    cout << '\n';
  }
}
