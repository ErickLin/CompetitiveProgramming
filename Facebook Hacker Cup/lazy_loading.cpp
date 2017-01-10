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
typedef long double ld;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<double> vd;
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
    int T;
    cin >> T;
    forf(t, T) {
        cout << "Case #" << t + 1 << ": ";
        int n;
        cin >> n;
        vi w(n);
        forf(i, n) {
            cin >> w[i];
        }
        sort(w.begin(), w.end());
        int left = 0, right = n - 1, trips = 0;
        while (w[right] >= 50) {
            trips++;
            right--;
        }
        int accum = w[right];
        while (left < right) {
            left++;
            accum += w[right];
            if (accum >= 50) {
                trips++;
                right--;
                accum = w[right];
            }
        }
        cout << trips << '\n';
    }
    return 0;
}
