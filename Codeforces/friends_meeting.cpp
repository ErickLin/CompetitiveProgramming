// 931A
#include <cmath>
#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  int d = abs(b - a);
  bool second_move = false;
  int tiredness = 0;
  int step = 1;
  while (d > 0) {
    tiredness += step;
    d--;
    second_move = !second_move;
    if (!second_move) {
      step++;
    }
  }
  cout << tiredness << '\n';
}
