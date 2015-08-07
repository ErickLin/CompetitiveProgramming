/*
ID: Jugglebrosjr2
LANG: C++
TASK: vans
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define BIGINT_LEN 400
typedef unsigned int u32;

struct bigint {
    vector<unsigned short> num;

    bigint() : num(BIGINT_LEN) {
    }

    bigint(u32 b) : num(BIGINT_LEN) {
        for (int i = BIGINT_LEN - 1; i >= 0; i--) {
            num[i] = b % 10;
            b /= 10;
        }
    }

    void set(u32 b) {
        for (int i = BIGINT_LEN - 1; i >= 0; i--) {
            num[i] = b % 10;
            b /= 10;
        }
    }

    void add(u32 b) {
        unsigned short carry = 0;
        for (int i = BIGINT_LEN - 1; i >= 0; i--) {
            int sum = num[i] + b % 10 + carry;
            num[i] = sum % 10;
            carry = sum / 10;
            b /= 10;
        }
    }

    void add(bigint a) {
        unsigned short carry = 0;
        for (int i = BIGINT_LEN - 1; i >= 0; i--) {
            int sum = num[i] + a.num[i] + carry;
            num[i] = sum % 10;
            carry = sum / 10;
        }
    }

    void subtract(bigint a) {
        unsigned short carry = 0;
        for (int i = BIGINT_LEN - 1; i >= 0; i--) {
            if (a.num[i] + carry > num[i]) {
                num[i] = 10 + num[i] - a.num[i] - carry;
                carry = 1;
            } else {
                num[i] = num[i] - a.num[i] - carry;
                carry = 0;
            }
        }
    }

    string toString() {
        bool leading = true;
        string s = "";
        for (size_t i = 0; i < num.size(); i++) {
            if (leading && num[i] != 0) {
                leading = false;
            }
            if (!leading) {
                s += num[i] + '0';
            }
        }
        if (s == "") {
            s += '0';
        }
        return s;
    }
};

struct state {
    int r, c;
    vector<vector<bool> > vis;

    state(int r, int c, vector<vector<bool> > vis) {
        this->r = r;
        this->c = c;
        this->vis = vis;
    }
};

bool operator<(const state &a, const state &b) {
    if (a.r == b.r) {
        if (a.c == b.c) {
            for (int i = 0; i < a.vis.size(); i++) {
                for (int j = 0; j < a.vis[0].size(); j++) {
                    if (a.vis[i][j] != b.vis[i][j]) {
                        return a.vis[i][j] < b.vis[i][j];
                    }
                }
            }
            return false;
        }
        return a.c < b.c;
    }
    return a.r < b.r;
}

map<state, bigint> dp;

bigint dfs(int r, int c, vector<vector<bool> > &vis, int numVis) {
    state now(r, c, vis);
    //cout << r << ' ' << c << ' ' << numVis << '\n';
    if (dp.find(now) != dp.end()) {
        return dp[now];
    }
    bigint ret(0);
    if (r == 0 && c == 0) {
        if (numVis == vis.size() * vis[0].size()) {
            ret.add(1);
        }
    } else {
        if (r > 0 && !vis[r - 1][c]) {
            vis[r - 1][c] = true;
            ret.add(dfs(r - 1, c, vis, numVis + 1));
            vis[r - 1][c] = false;
        }
        if (r < vis.size() - 1 && !vis[r + 1][c]) {
            vis[r + 1][c] = true;
            ret.add(dfs(r + 1, c, vis, numVis + 1));
            vis[r + 1][c] = false;
        }
        if (c > 0 && !vis[r][c - 1]) {
            vis[r][c - 1] = true;
            ret.add(dfs(r, c - 1, vis, numVis + 1));
            vis[r][c - 1] = false;
        }
        if (c < vis[0].size() - 1 && !vis[r][c + 1]) {
            vis[r][c + 1] = true;
            ret.add(dfs(r, c + 1, vis, numVis + 1));
            vis[r][c + 1] = false;
        }
    }
    dp[now] = ret;
    return ret;
}

int main() {
    ifstream fin("vans.in");
    ofstream fout("vans.out");
    int n;
    fin >> n;
    vector<vector<bool> > vis(4, vector<bool>(n));
    vis[1][0] = true;
    bigint a = dfs(1, 0, vis, 1);
    //double the number of answers due to reversing routes
    a.add(a);
    cout << a.toString() << '\n';
    return 0;
}
