// 859D
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

int main() {
  int n;
  cin >> n;
  // probability of team i winning against team j
  vvd p_winning(1 << n, vd(1 << n));
  forf(i, 1 << n) {
    forf(j, 1 << n) {
      cin >> p_winning[i][j];
      p_winning[i][j] /= 100;
    }
  }
  // probability of team i winning all rounds up to j
  vvd p_winning_round(1 << n, vd(n + 1));
  forf(i, 1 << n) {
    p_winning_round[i][0] = 1;
  }
  for (int round = 1; round <= n; round++) {
    forf(i, 1 << n) {
      int blksize = 1 << (round - 1);
      int blknum = i / blksize;
      int opponent_blknum;
      if (blknum % 2 == 0) {
        opponent_blknum = blknum + 1;
      } else {
        opponent_blknum = blknum - 1;
      }
      forf(k, blksize) {
        int opponent = opponent_blknum * blksize + k;
        p_winning_round[i][round] += p_winning_round[opponent][round - 1] * p_winning[i][opponent];
      }
      p_winning_round[i][round] *= p_winning_round[i][round - 1];
    }
  }
  /*
  for (int round = 1; round <= n; round++) {
  forf(i, 1 << n) {
    cout << p_winning_round[i][round] << ' ';
  }
    cout << '\n';
  }
  */

  // Propagate backward to compute best winning bracket.
  unordered_set<int> winning_teams;
  double expected_score = 0;
  for (int round = n; round >= 1; round--) {
    int blksize = 1 << round;
    int numblks = (1 << n) / blksize;
    for (int blknum = 0; blknum < numblks; blknum++) {
      double max_p = 0;
      int winning_team = blknum * blksize;
      bool used_up = false;
      forf(k, blksize) {
        int team = blknum * blksize + k;
        if (winning_teams.count(team)) {
          used_up = true;
          break;
        }
        if (max_p < p_winning_round[team][round]) {
          winning_team = team;
          max_p = p_winning_round[winning_team][round];
        }
      }
      if (!used_up) {
        winning_teams.insert(winning_team);
      }
    }
    // Add up points from all winning teams in this round
    for (int winner : winning_teams) {
      expected_score += p_winning_round[winner][round] * (1 << (round - 1));
    }
  }
  printf("%.10f\n", expected_score);
  return 0;
}
