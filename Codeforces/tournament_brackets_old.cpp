// 859D
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<double> vd;
typedef vector<vd> vvd;

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

  // Propagate backward to compute best winning bracket.
  unordered_set<int> winning_teams;
  double expected_score = 0;
  for (int round = n; round >= 1; round--) {
    int blksize = 1 << round;
    int numblks = (1 << n) / blksize;
    forf(blknum, numblks) {
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
    // Add up points from all winning teams in this round.
    for (int winner : winning_teams) {
      expected_score += p_winning_round[winner][round] * (1 << (round - 1));
    }
  }
  printf("%.10f\n", expected_score);
}
