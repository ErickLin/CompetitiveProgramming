// 549C
#include <iostream>
using namespace std;
typedef unsigned int u32;

int main() {
	//first index is number of odd cities remaining, second index " " num_even " "
	//vector<vector<bool> > strategy(200001, 200001);
	//strategy[0][0] = false;
	u32 n, k, num_odd = 0, num_even = 0;
	cin >> n >> k;
	for (u32 i = 0; i < n; i++) {
		u32 a;
		cin >> a;
		if ((a & (1 << 0)) == 1) {
			num_odd++;
		} else {
      num_even++;
    }
	}
  bool is_odd = num_odd % 2;
  bool last_is_stannis = (n - k) % 2 == 1;
  u32 num_moves_player = (n - k) / 2;
  if (n == k) {
    goto end;
  }
  if (num_moves_player < num_odd && num_moves_player < num_even) {
    is_odd = last_is_stannis;
  } else {
    if (last_is_stannis) {
      // num_odd != num_even.
      if (k % 2 == 0) {
        // Daenerys burns either all the odd cities or all the even cities,
        // whichever is fewer.
        is_odd = false;
        /*
        if (num_odd < num_even) {
          is_odd += num_odd;
        } else {
          is_odd += n - k - num_even;
        }
        */
      } else {
        // Daenerys tries to burn all the odd cities.
        is_odd = !(num_even == 0 || num_odd <= num_moves_player);
      }
    } else {
      if (k % 2 == 0) {
        is_odd = false;
      } else {
        // Stannis tries to burn all the even cities.
        is_odd = num_even <= num_moves_player;
      }
    }
  }
  end: cout << (is_odd ? "Stannis\n" : "Daenerys\n");
}
