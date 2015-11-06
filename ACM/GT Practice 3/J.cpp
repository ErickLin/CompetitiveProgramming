#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

/*
bool checkSat(vector<vector<int> > &exprs, vector<int> &vals, int i) {
    int n = exprs[0].size();
    int m = exprs.size();
    if (i == m) {
        return true;
    }
    bool sat = false;
    for (int j = 0; j < n; j++) {
        if (exprs[i][j] != 0) {
            if (vals[j] == 0) {
                vals[j] = exprs[i][j];
                sat = sat | checkSat(exprs, vals, i + 1);
                vals[j] = 0;
            } else if (vals[j] == exprs[i][j]) {
                sat = sat | checkSat(exprs, vals, i + 1);
            }
        }
    }
    return sat;
}
*/

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cin.ignore(256, '\n');
        vector<vector<int> > exprs(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            vector<int> expr(n);
            string line;
            getline(cin, line);
            int pos = 0;
            while (pos < line.size()) {
                string s = "";
                while (pos < line.size() && line.at(pos) != ' ') {
                    s += line.at(pos);
                    pos++;
                }
                pos += 3;
                int ind = s.at(s.size() - 1) - '1';
                expr[ind] = (s.at(0) == '~') ? -1 : 1;
            }
            exprs[i] = expr;
            /*
            for (int j = 0; j < n; j++) {
                cout << exprs[i][j] << ' ';
            }
            cout << '\n';
            */
        }
        /*
        vector<int> vals(n);
        if (checkSat(exprs, vals, 0)) {
            cout << "satisfiable\n";
        } else {
            cout << "unsatisfiable\n";
        }
        */
        bool sat = false;
        for (int i = 0; i < (1 << n) && !sat; i++) {
            bool sat2 = true;
            for (int j = 0; j < m && sat2; j++) {
                bool sat3 = false;
                for (int k = 0; k < n && !sat3; k++) {
                    if (((i & (1 << k)) == 0 && exprs[j][k] == -1)
                            || ((i & (1 << k)) != 0 && exprs[j][k] == 1)) {
                        sat3 = true;
                    }
                }
                if (!sat3) {
                    sat2 = false;
                }
            }
            if (sat2) {
                sat = true;
            }
        }
        if (sat) {
            cout << "satisfiable\n";
        } else {
            cout << "unsatisfiable\n";
        }
    }
    return 0;
}

