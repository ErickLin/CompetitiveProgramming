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
  // maximum expected score of team i after round j
  vvd e_score_round(1 << n, vd(n + 1));
  forf(i, 1 << n) {
    p_winning_round[i][0] = 1;
    e_score_round[i][0] = 0;
  }
  double max_e_score = 0;
  for (int round = 1; round <= n; round++) {
    forf(i, 1 << n) {
      int blksize = 1 << (round - 1);
      int blknum = i / blksize;
      int opps_blknum;
      if (blknum % 2 == 0) {
        opps_blknum = blknum + 1;
      } else {
        opps_blknum = blknum - 1;
      }
      forf(k, blksize) {
        int j = opps_blknum * blksize + k;
        p_winning_round[i][round] += p_winning_round[j][round - 1] * p_winning[i][j];
      }
      p_winning_round[i][round] *= p_winning_round[i][round - 1];
      forf(k, blksize) {
        int j = opps_blknum * blksize + k;
        e_score_round[i][round] = max(e_score_round[i][round],
            e_score_round[i][round - 1] + e_score_round[j][round - 1] +
            p_winning_round[i][round] * (1 << (round - 1)));
        if (round == n) {
          max_e_score = max(max_e_score, e_score_round[i][round]);
        }
      }
    }
  }
  printf("%.10f\n", max_e_score);
}
