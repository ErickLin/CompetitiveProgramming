#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void incSuperset(int s, vector<int> &countSuperset, int accum, int bit) {
    if (bit >= 16) {
        countSuperset[accum]++;
    } else {
        incSuperset(s, countSuperset, accum | (1 << bit), bit + 1);
        if ((s & (1 << bit)) == 0) {
            incSuperset(s, countSuperset, accum, bit + 1);
        }
    }
}

void decSuperset(int s, vector<int> &countSuperset, int accum, int bit) {
    if (bit >= 16) {
        countSuperset[accum]--;
    } else {
        decSuperset(s, countSuperset, accum | (1 << bit), bit + 1);
        if ((s & (1 << bit)) == 0) {
            decSuperset(s, countSuperset, accum, bit + 1);
        }
    }
}

void incSubset(int s, vector<int> &countSubset, int accum, int bit) {
    if (bit >= 16) {
        countSubset[accum]++;
    } else {
        incSubset(s, countSubset, accum, bit + 1);
        if ((s & (1 << bit)) == (1 << bit)) {
            incSubset(s, countSubset, accum | (1 << bit), bit + 1);
        }
    }
}

void decSubset(int s, vector<int> &countSubset, int accum, int bit) {
    if (bit >= 16) {
        countSubset[accum]--;
    } else {
        decSubset(s, countSubset, accum, bit + 1);
        if ((s & (1 << bit)) == (1 << bit)) {
            decSubset(s, countSubset, accum | (1 << bit), bit + 1);
        }
    }
}

int getTotal(int s, vector<int> &count, int accum, int bit) {
    if (bit >= 16) {
        return count[accum];
    } else {
        int ret = getTotal(s, count, accum, bit + 1);
        if ((s & (1 << bit)) == (1 << bit)) {
            ret += getTotal(s, count, accum | (1 << bit), bit + 1);
        }
        return ret;
    }
}

int flip(int s) {
    int notS = 0;
    for (int i = 0; i < 16; i++) {
        if ((s & (1 << i)) == 0) {
            notS |= (1 << i);
        }
    }
    return notS;
}

int numCommonBits(int a, vector<int> &countSubset, int accum, int bit, int bitsLeft) {
    if (bitsLeft == 0) {
        return countSubset[accum];
    } else if (bit < 16) {
        int ret = numCommonBits(a, countSubset, accum, bit + 1, bitsLeft);
        if ((a & (1 << bit)) == (1 << bit)) {
            ret += numCommonBits(a, countSubset, accum | (1 << bit), bit + 1, bitsLeft - 1);
        }
        return ret;
    }
    return 0;
}

int main() {
    vector<int> count(1 << 16);
    vector<int> countSuperset(1 << 16);
    vector<int> countSubset(1 << 16);
    int numMost8 = 0;
    int q;
    cin >> q;
    while (q--) {
        string cmd;
        int s;
        cin >> cmd >> s;
        if (cmd == "add") {
            if (__builtin_popcount(s) > 8) {
                incSuperset(s, countSuperset, 0, 0);
            } else {
                count[s]++;
                numMost8++;
                incSubset(s, countSubset, 0, 0);
            }
        } else if (cmd == "del") {
            if (__builtin_popcount(s) > 8) {
                decSuperset(s, countSuperset, 0, 0);
            } else {
                count[s]--;
                numMost8--;
                decSubset(s, countSubset, 0, 0);
            }
        } else {
            int ans;
            if (__builtin_popcount(s) > 8) {
                ans = countSuperset[s] + numMost8;
                // Inclusion-Exclusion Principle to subtract off numbers that have
                // at least one bit in common with the negation of s
                int notS = flip(s);
                for (int i = 1; i <= 8; i += 2) {
                    ans -= numCommonBits(notS, countSubset, 0, 0, i);
                }
                for (int i = 2; i <= 8; i += 2) {
                    ans += numCommonBits(notS, countSubset, 0, 0, i);
                }
            } else {
                ans = getTotal(s, count, 0, 0);
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
