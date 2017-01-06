#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

int main() {
    string s;
    cin >> s;
    int rank = 25, stars = 0, consec = 0;
    forf(i, s.size()) {
        if (rank == 0) {
            break;
        }
        if (s[i] == 'W') {
            int beginrank = rank;
            stars++;
            int need = 2;
            if (rank <= 20) {
                need = 3;
            }
            if (rank <= 15) {
                need = 4;
            }
            if (rank <= 10) {
                need = 5;
            }
            if (stars > need) {
                rank--;
                stars = 1;
            }
            consec++;
            if (consec >= 3 && beginrank >= 6) {
                stars++;
            }
            if (stars > need) {
                rank--;
                stars = 1;
            }
        } else {
            consec = 0;
            if (rank > 20 || (rank == 20 && stars == 0)) {
                continue;
            }
            stars--;
            if (stars < 0) {
                rank++;
                if (rank >= 1) {
                    stars = 4;
                }
                if (rank >= 11) {
                    stars = 3;
                }
                if (rank >= 16) {
                    stars = 2;
                }
            }
        }
    }
    if (rank == 0) {
        cout << "Legend\n";
    } else {
        cout << rank << '\n';
    }
    return 0;
}
