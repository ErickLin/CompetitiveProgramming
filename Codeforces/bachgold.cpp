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

vb sieve(int n) {
    vb isPrime(n + 1);
    for (int i = 2; i <= n; i++) {
        isPrime[i] = true;
    }
    for (int i = 2; i <= (int) (ceil(sqrt(n))); i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

int main() {
    int n;
    cin >> n;
    //vb isPrime = sieve(n);
    cout << n/2 << '\n';
    for (int i = 0; i < n/2 - 1; i++) {
        cout << "2 ";
    }
    if (n % 2) {
        cout << "3\n";
    } else {
        cout << "2\n";
    }
    return 0;
}
