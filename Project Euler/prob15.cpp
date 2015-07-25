#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<vector<long long> > comb(41, vector<long long>(41));
  for (long long i = 0; i <= 40; i++) {
    comb[i][0] = 1;
    for (long long j = 1; j <= i; j++) {
      comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
    }
  }
  cout << comb[4][2] << '\n';
  cout << comb[40][20] << '\n';
}
