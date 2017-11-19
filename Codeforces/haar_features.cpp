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
  vvi coeffs(n, vi(m));
  forb(i, n) {
    forb(j, m) {
      int req_coeff = feature[i][j] == 'W' ? 1 : -1;
      if (coeffs[i][j] != req_coeff) {
        num_ops++;
        forf2(a, i) {
          forf2(b, j) {
            int d_coeff = req_coeff - coeffs[i][j];
            coeffs[a][b] += d_coeff;
          }
        }
      }
    }
  }
  cout << num_ops << '\n';
}
