// 932C
#include <iostream>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  vii lin_comb_coeffs(1000001);
  lin_comb_coeffs[a] = mp(1, 0);
  lin_comb_coeffs[b] = mp(0, 1);
  forf(i, 1000000) {
    if (lin_comb_coeffs[i].first != 0 || lin_comb_coeffs[i].second != 0) {
      if (i + a <= 1000000) {
        lin_comb_coeffs[i + a] = mp(lin_comb_coeffs[i].first + 1,
                                    lin_comb_coeffs[i].second);
      }
      if (i + b <= 1000000) {
        lin_comb_coeffs[i + b] = mp(lin_comb_coeffs[i].first,
                                    lin_comb_coeffs[i].second + 1);
      }
    }
  }
  if (lin_comb_coeffs[n] == mp(0, 0)) {
    cout << "-1\n";
    return 0;
  }
  //cout << lin_comb_coeffs[n].first << ' ' << lin_comb_coeffs[n].second << '\n';
  vi p(n);
  int k = 1;
  forf(i, lin_comb_coeffs[n].first) {
    int starting = k;
    forf(j, a - 1) {
      p[k - 1] = k + 1;
      k++;
    }
    p[k - 1] = starting;
    k++;
  }
  forf(i, lin_comb_coeffs[n].second) {
    int starting = k;
    forf(j, b - 1) {
      p[k - 1] = k + 1;
      k++;
    }
    p[k - 1] = starting;
    k++;
  }
  forf(i, n - 1) {
    cout << p[i] << ' ';
  }
  cout << p[n - 1] << '\n';
}
