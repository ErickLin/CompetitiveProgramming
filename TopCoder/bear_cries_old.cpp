#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<pair<int, int> > vii;
typedef vector<ll> vll;
typedef vector<vector<ll> > vvll;
const int MOD = 1000000007;

vector<vector<long long> > comb(201, vector<long long>(201));

class BearCries {
    public:
        ll recurse(string &message, int pos, int started, int startedPrev, int underscore) {
            //cout << "pos: " << pos << "  started: " << started << "  startedPrev: " << startedPrev << "  underscore: " << underscore << '\n';
            if (pos == message.size()) {
                if (started == 0 && underscore == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
            if (message.at(pos) == '_') {
                return recurse(message, pos + 1, started, 0, underscore + 1);
            } else{
                ll ret = recurse(message, pos + 1, started + 1, startedPrev + 1, underscore) % MOD;
                if (started > 0 && underscore > 0) {
                    for (int u = 1; u <= underscore; u++) {
                        ret = (ret + (started - startedPrev) * (comb[underscore][u] * recurse(message, pos + 1, started - 1, startedPrev, underscore - u) % MOD) % MOD) % MOD;
                    }
                }
                return ret;
            }
        }

        int count(string message) {
            if (message.at(0) == '_' || message.at(message.size() - 1) == '_') {
                return 0;
            }
            int n = 0;
            for (int i = 0; i < message.size(); i++) {
                if (message.at(i) == ';') {
                    n++;
                }
            }
            if (n % 2 == 1) {
                return 0;
            } else {
                return recurse(message, 0, 0, 0, 0);
            }
        }
};

int main() {
    comb[0][0] = 1;
    for (int i = 0; i <= 200; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
        }
    }
    BearCries a;
    cout << a.count(";_;;_____;") << '\n';
    cout << a.count(";;;___;;;") << '\n';
    cout << a.count("_;__;") << '\n';
    cout << a.count(";_____________________________________;") << '\n';
    cout << a.count(";__;____;") << '\n';
    cout << a.count(";_;;__;_;;") << '\n';
}
