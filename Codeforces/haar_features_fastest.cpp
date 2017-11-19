// 549D
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
#define forf2(i, n) for (int i = 0; i <= n; i++)
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;

int main() {
  int n, m;
  cin >> n >> m;
  vvc feature(n, vc(m));
  forf(i, n) {
    forf(j, m) {
      cin >> feature[i][j];
    }
  }
  int num_ops = 0;
  vi coeffs_by_col(m);
  forb(i, n) {
    int running_coeff_sum_along_row = 0;
    forb(j, m) {
      int req_coeff = feature[i][j] == 'W' ? 1 : -1;
      coeffs_by_col[j] += running_coeff_sum_along_row;
      if (coeffs_by_col[j] != req_coeff) {
        num_ops++;
        int d_coeff = req_coeff - coeffs_by_col[j];
        coeffs_by_col[j] += d_coeff;
        running_coeff_sum_along_row += d_coeff;
      }
    }
  }
  cout << num_ops << '\n';
}
