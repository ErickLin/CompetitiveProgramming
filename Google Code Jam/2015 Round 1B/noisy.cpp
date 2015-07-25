#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
typedef unsigned int u32;
typedef unsigned long long u64;
vector<vector<u32> > wt(10000, vector<u32>(10000));
u32 r, c, n;

bool compare(pair<u32, u32> a, pair<u32, u32> b)
{
    if (wt[a.first][a.second] == wt[b.first][b.second]) {
        return abs(a.first - r / 2) + abs(a.second - c / 2) > abs(b.first - r / 2) + abs(b.second - c / 2);
    }
    return wt[a.first][a.second] < wt[b.first][b.second];
}

int main() {
	//ios_base::sync_with_stdio(false);
    ifstream fin("B-small-attempt3.in");
    ofstream fout("noisy.out");
    u32 t;
    fin >> t;
    for (u32 i = 1; i <= t; i++) {
        fin >> r >> c >> n;
        if (r == 1 && c == 1) {
            fout << "Case #" << i << ": 0\n";
            continue;
        }
        u32 min = r * (c + 1) + c * (r + 1) - 2 * (r + c);
        bool isRect = r > 1 && c > 1;
        for (u32 x = 1; x < c - 1; x++) {
            wt[0][x] = 2 + isRect;
            wt[r - 1][x] = 2 + isRect;
        }
        for (u32 y = 1; y < r - 1; y++) {
            wt[y][0] = 2 + isRect;
            for (u32 x = 1; x < c - 1; x++) {
                wt[y][x] = 3 + isRect;
            }
            wt[y][c - 1] = 2 + isRect;
        }
        wt[0][0] = 1 + isRect;
        wt[r - 1][0] = 1 + isRect;
        wt[0][c - 1] = 1 + isRect;
        wt[r - 1][c - 1] = 1 + isRect;
        vector<pair<u32, u32> > rooms(r * c);
        u32 ind = 0;
        for (u32 y = 0; y < r; y++) {
            for (u32 x = 0; x < c; x++) {
                rooms[ind++] = make_pair(y, x);
            }
        }
        for (u32 numLeft = r * c; numLeft > n; numLeft--) {
            /*
            for (u32 i = 0; i < numLeft; i++) {
                cout << "Order 1: " << rooms[i].first << ' ' << rooms[i].second << ' ' << wt[rooms[i].first][rooms[i].second] << '\n';
            }
            */
            sort(rooms.begin(), rooms.end(), compare);
            /*
            for (u32 i = 0; i < numLeft; i++) {
                cout << "Order 2: " << rooms[i].first << ' ' << rooms[i].second << ' ' << wt[rooms[i].first][rooms[i].second] << '\n';
            }
            */
            u32 hiR = rooms[numLeft - 1].first;
            u32 hiC = rooms[numLeft - 1].second;
            //cout << hiR << ' ' << hiC << ' ' << wt[hiR][hiC] << '\n';
            min -= wt[hiR][hiC];
            if (hiR > 0) {
                wt[hiR - 1][hiC]--;
            }
            if (hiR < r - 1) {
                wt[hiR + 1][hiC]--;
            }
            if (hiC > 0) {
                wt[hiR][hiC - 1]--;
            }
            if (hiC < c - 1) {
                wt[hiR][hiC + 1]--;
            }
            rooms.erase(rooms.end() - 1);
        }
        fout << "Case #" << i << ": " << min << '\n';
        //cout << '\n';
    }
    return 0;
}