#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
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

typedef string player;
typedef pair<string, string> team;

int main() {
  int n;
  cin >> n;
  vector<player> players(n);
  forf(i, n) {
    cin >> players[i];
  }
  string wins;
  cin >> wins;

  team white = mp(players[0], players[2]), black = mp(players[1], players[3]);
  team white_ordered = white, black_ordered = black;
  queue<player> waiting;
  for (int i = 4; i < players.size(); i++) {
    waiting.push(players[i]);
  }

  int white_streak = 0, black_streak = 0, longest_streak = 0;
  vector<team> longest_dynasties;
  for (char c : wins) {
    if (c == 'W') {
      white_streak++;
      if (white_streak > longest_streak) {
        longest_dynasties.clear();
        longest_streak = white_streak;
      }
      if (white_streak == longest_streak) {
        longest_dynasties.push_back(white_ordered);
      }
      white = mp(white.second, white.first);

      black_streak = 0;
      waiting.push(black.second);
      black = mp(waiting.front(), black.first);
      waiting.pop();
      // The new defense player was at the table earlier.
      black_ordered = mp(black.second, black.first);
    } else {
      black_streak++;
      if (black_streak > longest_streak) {
        longest_dynasties.clear();
        longest_streak = black_streak;
      }
      if (black_streak == longest_streak) {
        longest_dynasties.push_back(black_ordered);
      }
      black = mp(black.second, black.first);

      white_streak = 0;
      waiting.push(white.second);
      white = mp(waiting.front(), white.first);
      waiting.pop();
      // The new defense player was at the table earlier.
      white_ordered = mp(white.second, white.first);
    }
  }
  for (team dynasty : longest_dynasties) {
    cout << dynasty.first << ' ' << dynasty.second << '\n';
  }
}
