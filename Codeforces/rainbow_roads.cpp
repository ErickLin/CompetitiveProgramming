// 908F
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<char> vc;

int main() {
  int n;
  cin >> n;
  vi pos(n);
  vc colors(n);
  forf(i, n) {
    cin >> pos[i] >> colors[i];
  }

  // positions of nearest points of each color
  map<char, vi> prev, next;
  // positions of first and last points of each color
  map<char, int> first, last;
  for (char color : {'G', 'R', 'B'}) {
    prev[color].resize(n);
    int running_prev = 0;
    forf(i, n) {
      if (running_prev) {
        prev[color][i] = running_prev;
      }
      if (colors[i] == color) {
        running_prev = pos[i];
        if (!first.count(color)) {
          first[color] = pos[i];
        }
      }
    }
    next[color].resize(n);
    int running_next = 0;
    forb(i, n) {
      if (running_next) {
        next[color][i] = running_next;
      }
      if (colors[i] == color) {
        running_next = pos[i];
        if (!last.count(color)) {
          last[color] = pos[i];
        }
      }
    }
  }

  vb done(n);
  ll min_cost = 0;
  vi R_window, B_window;
  int R_max_gap = 0, B_max_gap = 0;
  // phase 1 (connect all green points)
  forf(i, n) {
    if (!prev['G'][i]) {
      continue;
    }
    switch (colors[i]) {
      case 'G':
        if (!R_window.empty()) {
          R_max_gap = max(R_max_gap, pos[i] - pos[R_window.back()]);
        }
        if (!B_window.empty()) {
          B_max_gap = max(B_max_gap, pos[i] - pos[B_window.back()]);
        }
        {
          int x = pos[i] - prev['G'][i];
          if (R_window.empty() && B_window.empty()) {
            min_cost += x;
          } else if (R_window.empty()) {
            min_cost += x + x - B_max_gap;
          } else if (B_window.empty()) {
            min_cost += x + x - R_max_gap;
          } else {
            min_cost += x + x + min(x - R_max_gap - B_max_gap, 0);
          }
        }
        for (int i : R_window) {
          done[i] = true;
        }
        for (int i : B_window) {
          done[i] = true;
        }
        R_window.clear();
        B_window.clear();
        R_max_gap = 0;
        B_max_gap = 0;
        break;
      case 'R':
        if (R_window.empty()) {
          R_max_gap = pos[i] - prev['G'][i];
        } else {
          R_max_gap = max(R_max_gap, pos[i] - pos[R_window.back()]);
        }
        R_window.pb(i);
        break;
      case 'B':
      default:
        if (B_window.empty()) {
          B_max_gap = pos[i] - prev['G'][i];
        } else {
          B_max_gap = max(B_max_gap, pos[i] - pos[B_window.back()]);
        }
        B_window.pb(i);
    }
  }
  // phase 2 (connect any remaining points)
  for (char color : {'R', 'B'}) {
    if (!first.count(color)) {
      continue;
    }
    if (first.count('G')) {
      if (first[color] < first['G']) {
        min_cost += first['G'] - first[color];
      }
      if (last[color] > last['G']) {
        min_cost += last[color] - last['G'];
      }
    } else {
      min_cost += last[color] - first[color];
    }
  }
  cout << min_cost << '\n';
}
