#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    printf("Case #%d: ", t);
    int n;
    scanf("%d", &n);
    vi v(n);
    forf(i, n) {
      scanf("%d", &v[i]);
    }
    bool done = false;
    while (!done) {
      done = true;
      forf(i, v.size() - 2) {
        if (v[i] > v[i + 2]) {
          done = false;
          int temp = v[i];
          v[i] = v[i + 2];
          v[i + 2] = temp;
        }
      }
    }
    bool found = false;
    forf(i, v.size() - 1) {
      if (v[i] > v[i + 1]) {
        printf("%d\n", i);
        found = true;
        break;
      }
    }
    if (!found) {
      printf("OK\n");
    }
  }
}
