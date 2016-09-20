#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    vector<ll> tetra(1000);
    tetra[1] = 1;
    for (int i = 2; i <= 999; i++) {
        tetra[i] = tetra[i - 1] + i * (i + 1)/2;
    }
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int s;
        cin >> s;
        cout << i << ": " << s << " " << tetra[s] << '\n';
    }
    return 0;
}
