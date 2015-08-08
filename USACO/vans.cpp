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

#define BIGINT_LEN 499
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

int main() {
    ifstream fin("vans.in");
    ofstream fout("vans.out");
    int n;
    fin >> n;
    vector<vector<bigint> > dp(n, vector<bigint>(6));
    bigint a(1);
    if (n > 1) {
        dp[1][0] = dp[1][1] = a;
    }
    for (int i = 2; i < n; i++) {
        dp[i][0].add(dp[i - 1][0]);
        dp[i][0].add(dp[i - 1][2]);
        dp[i][0].add(dp[i - 1][4]);
        dp[i][1] = dp[i][0];
        dp[i][1].add(dp[i - 1][3]);
        dp[i][2].add(dp[i - 1][1]);
        dp[i][2].add(dp[i - 1][5]);
        dp[i][3] = dp[i - 1][1];
        dp[i][4] = dp[i][2];
        dp[i][5] = dp[i][2];
    }
    a = dp[n - 1][1];
    a.add(dp[n - 1][5]);
    //double the number of answers due to reversing routes
    a.add(a);
    fout << a.toString() << '\n';
    return 0;
}
