#include <vector>
#include <string>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

class HamiltonianPathsInGraph {
 public:
  vi findPath(vector<string> X) {
    vi path;
    if (X[0][1] == '+') {
      path.pb(0);
      path.pb(1);
    } else {
      path.pb(1);
      path.pb(0);
    }
    int n = X.size();
    for (int i = 2; i < n; i++) {
      if (X[i][path[0]] == '+') {
        path.insert(path.begin(), i);
      } else if (X[path[i - 1]][i] == '+') {
        path.pb(i);
      } else for (int j = 0; j < i - 1; j++) {
        if (X[path[j]][i] == '+' && X[i][path[j + 1]] == '+') {
          path.insert(path.begin() + j + 1, i);
          break;
        }
      }
    }
    return path;
  }
};
