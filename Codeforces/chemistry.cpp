#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a;
    map<long long, int> count;
    map<long long, int> qTurns;
    map<long long, int> qNum;
    map<long long, int> moves;
    long long minMoves = LONG_MAX;
    for (int i = 0; i < n; i++) {
        long long temp;
        cin >> temp;
        a.push_back(temp);
        count[a[i]]++;
        if (count[a[i]] == n && moves[a[i]] < minMoves)
            minMoves = moves[a[i]];
        /*
        if (count[a[i]] > n) {
            cout << a[i] << '\n';
        }
        */
        int b = (a[i] >> 1);
        if (b != 0 && (b << 1) != a[i]) {
            qTurns[b << 1] += 2;
            qNum[b << 1]++;
        }
        for (int t = 1; ; t++) {
            count[b]++;
            moves[b] += t;
            /*
            if (count[b] > n) {
                cout << b << '\n';
            }
            */
            if (count[b] == n && moves[b] < minMoves)
                minMoves = moves[b];
            if (b <= 0) {
                break;
            } else {
                int c = (b >> 1) << 1;
                if (c != 0 && c != b) {
                    qTurns[c] += t + 2;
                    qNum[c]++;
                }
                b >>= 1;
            }
        }
        b = (a[i] << 1);
        for (int t = 1; ; t++) {
            count[b]++;
            moves[b] += t;
            /*
            if (count[b] > n) {
                cout << b << '\n';
            }
            */
            if (count[b] == n && moves[b] < minMoves)
                minMoves = moves[b];
            if ((b << 1) > 100000) {
                break;
            } else {
                b <<= 1;
            }
        }
    }
    for (map<long long, int>::iterator it = qTurns.begin(); it != qTurns.end(); it++) {
        int c = it->first;
        int t = it->second;
        int dt = qNum[c];
        for (int t2 = t; ; t2 += dt) {
            count[c] += dt;
            moves[c] += t2;
            //cout << c << ' ' << b << ' ' << t2 << '\n';
            if (count[c] == n && moves[c] < minMoves)
                minMoves = moves[c];
            if ((c << 1) > 100000) {
                break;
            } else {
                c <<= 1;
            }
        }
    }
    cout << minMoves << '\n';
    return 0;
}
