// 908B
#include <iostream>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<char> vc;
typedef vector<vc> vvc;

typedef pair<int, int> loc;
int main() {
  int n, m;
  cin >> n >> m;
  vvc maze(n, vc(m));
  loc start, end;
  forf(i, n) {
    forf(j, m) {
      cin >> maze[i][j];
      if (maze[i][j] == 'S') {
        start = mp(i, j);
      }
      if (maze[i][j] == 'E') {
        end = mp(i, j);
      }
    }
  }
  string s;
  cin >> s;

  string dir_mappings = "DLRU";
  sort(dir_mappings.begin(), dir_mappings.end());
  int num_valid_mappings = 0;
  do {
    bool valid = false;
    loc cur = start;
    for (char c : s) {
      int idx = c - '0';
      switch (dir_mappings[idx]) {
        case 'D':
          cur = mp(cur.first + 1, cur.second);
          break;
        case 'L':
          cur = mp(cur.first, cur.second - 1);
          break;
        case 'R':
          cur = mp(cur.first, cur.second + 1);
          break;
        case 'U':
        default:
          cur = mp(cur.first - 1, cur.second);
      }
      if (cur.first < 0 || cur.first >= n || cur.second < 0 || cur.second >= m || maze[cur.first][cur.second] == '#') {
        break;
      }
      if (cur == end) {
        //cout << dir_mappings << '\n';
        valid = true;
        break;
      }
    }
    if (valid) {
      num_valid_mappings++;
    }
  } while (next_permutation(dir_mappings.begin(), dir_mappings.end()));
  cout << num_valid_mappings << '\n';
}
