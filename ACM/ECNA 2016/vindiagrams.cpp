#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;

typedef pii loc;

vector<loc> get_neighbors(loc cur_loc, vvc& grid, int n, int m) {
  int i = cur_loc.first, j = cur_loc.second;
  unordered_set<char> labels({'X', 'A', 'B'});
  vector<loc> neighbors;
  if (i > 0 && labels.count(grid[i - 1][j])) {
    neighbors.push_back(mp(i - 1, j));
  }
  if (i < n - 1 && labels.count(grid[i + 1][j])) {
    neighbors.push_back(mp(i + 1, j));
  }
  if (j > 0 && labels.count(grid[i][j - 1])) {
    neighbors.push_back(mp(i, j - 1));
  }
  if (j < m - 1 && labels.count(grid[i][j + 1])) {
    neighbors.push_back(mp(i, j + 1));
  }
  return neighbors;
}

int main() {
  int n, m;
  cin >> n >> m;
  vvc grid(n, vc(m));
  map<char, loc> starting_locs;
  forf(i, n) {
    forf(j, m) {
      cin >> grid[i][j];
      for (char label : {'A', 'B'}) {
        if (grid[i][j] == label) {
          starting_locs[label] = mp(i, j);
        }
      }
    }
  }
  for (char label : {'A', 'B'}) {
    queue<loc> q;
    q.push(starting_locs[label]);
    vvb visited(n, vb(m));
    visited[starting_locs[label].first][starting_locs[label].second] = true;
    while (!q.empty()) {
      loc cur = q.front();
      q.pop();
      int i = cur.first, j = cur.second;
      grid[i][j] = label;
      for (loc neighbor : get_neighbors(cur, grid, n, m)) {
        if (!visited[neighbor.first][neighbor.second]) {
          visited[neighbor.first][neighbor.second] = true;
          if (get_neighbors(neighbor, grid, n, m).size() > 2) {
            loc next_neighbor = mp(neighbor.first + neighbor.first - cur.first,
                neighbor.second + neighbor.second - cur.second);
            if (!visited[next_neighbor.first][next_neighbor.second]) {
              visited[next_neighbor.first][next_neighbor.second] = true;
              q.push(next_neighbor);
            }
          } else {
            q.push(neighbor);
          }
        }
      }
    }
  }

  vvb a_temp(n, vb(m)), b_temp(n, vb(m));
  map<char, vvb> inside_loop;
  inside_loop['A'] = a_temp;
  inside_loop['B'] = b_temp;
  for (char label : {'A', 'B'}) {
    forf(i, n) {
      forf(j, m) {
        inside_loop[label][i][j] = true;
      }
    }
    unordered_set<char> boundaries({'X', label});
    forf(i, n) {
      if (!boundaries.count(grid[i][0])) {
        inside_loop[label][i][0] = false;
      }
      if (!boundaries.count(grid[i][m - 1])) {
        inside_loop[label][i][m - 1] = false;
      }
    }
    forf(j, m) {
      if (!boundaries.count(grid[0][j])) {
        inside_loop[label][0][j] = false;
      }
      if (!boundaries.count(grid[n - 1][j])) {
        inside_loop[label][n - 1][j] = false;
      }
    }
  }

  for (char label : {'A', 'B'}) {
    unordered_set<char> boundaries({'X', label});
    vvb visited(n, vb(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (!inside_loop[label][i][j] && !visited[i][j]) {
          visited[i][j] = true;
          stack<loc> s;
          s.push(mp(i, j));
          while (!s.empty()) {
            loc cur = s.top();
            s.pop();
            vector<loc> neighbors({mp(cur.first, cur.second - 1), mp(cur.first - 1, cur.second), mp(cur.first, cur.second + 1), mp(cur.first + 1, cur.second)});
            for (loc neighbor : neighbors) {
              if (neighbor.first < 0 || neighbor.first >= n) {
                continue;
              }
              if (neighbor.second < 0 || neighbor.second >= m) {
                continue;
              }
              if (!boundaries.count(grid[neighbor.first][neighbor.second]) && !visited[neighbor.first][neighbor.second]) {
                inside_loop[label][neighbor.first][neighbor.second] = false;
                visited[neighbor.first][neighbor.second] = true;
                s.push(mp(neighbor.first, neighbor.second));
              }
            }
          }
        }
      }
    }
  }

  map<char, int> excluded_area;
  int intersection_area = 0;
  forf(i, n) {
    forf(j, m) {
      if (grid[i][j] == '.') {
        if (inside_loop['A'][i][j] && inside_loop['B'][i][j]) {
          intersection_area++;
          //cout << (char)'c';
        } else for (char label : {'A', 'B'}) {
          if (inside_loop[label][i][j]) {
            excluded_area[label]++;
            //cout << (char)(label - 'A' + 'a');
          }
        }
        /*
        if (!inside_loop['A'][i][j] && !inside_loop['B'][i][j]) {
          cout << grid[i][j];
        }
        */
      }/* else {
        cout << grid[i][j];
      }*/
    }
    //cout << '\n';
  }
  cout << excluded_area['A'] << ' ' << excluded_area['B'] << ' ' <<
      intersection_area << '\n';
}
