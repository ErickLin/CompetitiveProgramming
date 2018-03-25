// 957B
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define ins insert
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<char> vc;
typedef vector<vc> vvc;

int main() {
  int n, m; cin >> n >> m;
  vvc grid(n, vc(m));
  set<ll> bit_reps;
  forf(i, n) {
    ll bit_rep = 0;
    forf(j, m) {
      cin >> grid[i][j];
      bit_rep |= grid[i][j] == '#';
      bit_rep <<= 1;
    }
    for (ll other_bit_rep : bit_reps) {
      if ((bit_rep & other_bit_rep) && bit_rep != other_bit_rep) {
        cout << "No\n";
        return 0;
      }
    }
    bit_reps.ins(bit_rep);
  }
  cout << "Yes\n";
}
