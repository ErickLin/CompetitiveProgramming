#include <algorithm>
#include <cmath>
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

double d(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

/*
bool angleAllowed(int angle, double xF, double yF) {
    if (xF > 0 && yF > 0) {
        return angle == 7 || angle <= 3;
    } else if (xF < 0 && yF > 0) {
        return angle >= 1 && angle <= 5;
    } else if (xF < 0 && yF < 0) {
        return angle >= 3 && angle <= 7;
    } else if (xF > 0 && yF < 0) {
        return angle >= 5 || angle <= 1;
    } else {
        return true;
    }
}
*/

int main() {
    int n;
    cin >> n;
    while (n--) {
        int secs;
        double xF, yF;
        cin >> secs >> xF >> yF;
        double minDist = 200.0;
        vi start(5);
        queue<vi> q;
        q.push(start);
        map<vi, int> times;
        times[start] = 0;
        while (!q.empty()) {
            vi cur = q.front();
            q.pop();
            double x = 0.0, y = 0.0;
            for (int i = 0; i < 4; i++) {
                x += cur[i] * cos(45*i * M_PI / 180.0) * 10;
                y += cur[i] * sin(45*i * M_PI / 180.0) * 10;
            }
            if (d(x, y, xF, yF) < minDist) {
                minDist = d(x, y, xF, yF);
                /*
                cout << times[cur] << ' ' << x << ' ' << y << ' ' << minDist << ' ';
                for (int i = 0; i < 4; i++) {
                    cout << cur[i] << ' ';
                }
                cout << '\n';
                */
            }
            if (times[cur] < secs/* && d(x, y, xF, xF) <= (secs - times[cur]) * 10*/) {
                //if (angleAllowed(cur[4], xF, yF)) {
                vi forward(5);
                forward = cur;
                if (forward[4] < 4) {
                    forward[forward[4] % 4]++;
                } else {
                    forward[forward[4] % 4]--;
                }
                if (times.find(forward) == times.end()) {
                    q.push(forward);
                    times[forward] = times[cur] + 1;
                }
                //}
                vi turn(5);
                turn = cur;
                turn[4] = (turn[4] - 1 + 8) % 8;
                if (times.find(turn) == times.end()) {
                    q.push(turn);
                    times[turn] = times[cur] + 1;
                }
            }
        }
        cout << fixed << setprecision(6) << minDist << '\n';
    }
    return 0;
}
