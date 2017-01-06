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

bool isAlphanumeric(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n;
        vs users(n);
        forf(i, n) {
            cin >> users[i];
        }
        cin >> m;
        cin.ignore(1, '\n');
        vs msgs(m);
        forf(j, m) {
            getline(cin, msgs[j]);
        }
        bool possible = true;
        vs senders(m);
        vector<set<string> > choices(m);
        forf(j, m) {
            senders[j] = msgs[j].substr(0, msgs[j].find(":", 0));
            if (senders[j].compare("?") == 0) {
                forf(i, n) {
                    if (senders[j].compare(users[i]) == 0) {
                        continue;
                    }
                    if (j > 0 && senders[j - 1].compare(users[i]) == 0) {
                        continue;
                    }
                    choices[j].insert(users[i]);
                    size_t pos = msgs[j].find(users[i], 0);
                    while (pos != string::npos) {
                        //cout << msgs[j][pos - 1] << ' ' << msgs[j][pos + users[i].length()] << '\n';
                        if ((pos == 0 || !isAlphanumeric(msgs[j][pos - 1])) && (pos + users[i].length() == msgs[j].length() || !isAlphanumeric(msgs[j][pos + users[i].length()]))) {
                            choices[j].erase(users[i]);
                            break;
                        }
                        pos = msgs[j].find(users[i], pos + 1);
                    }
                }
            }
        }
        for (int j = 0; j < m - 1; j++) {
            choices[j].erase(senders[j + 1]);
        }
        forf(k, m) {
            forf(j, m) {
                if (senders[j].compare("?") == 0) {
                    if (choices[j].size() == 1) {
                        senders[j] = *choices[j].begin();
                        if (j > 0) {
                            choices[j - 1].erase(senders[j]);
                        }
                        if (j < m - 1) {
                            choices[j + 1].erase(senders[j]);
                        }
                    } else if (choices[j].size() == 0) {
                        possible = false;
                    }
                }
            }
        }
        if (possible) {
            forf(j, m) {
                if (senders[j].compare("?") == 0) {
                    senders[j] = *choices[j].begin();
                    if (j < m - 1) {
                        choices[j + 1].erase(senders[j]);
                    }
                }
            }
        }
        if (possible) {
            forf(j, m) {
                cout << senders[j] << msgs[j].substr(msgs[j].find(":", 0)) << '\n';
            }
        } else {
            cout << "Impossible\n";
        }
    }
    return 0;
}
