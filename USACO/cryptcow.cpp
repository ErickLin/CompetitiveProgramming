/*
ID: Jugglebrosjr2
LANG: C++
TASK: cryptcow
*/
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#define MOD 7900001
typedef unsigned int u32;

bitset<MOD> hashTable;

u32 elfHash(void *key, int len) {
    unsigned char *p = static_cast<unsigned char*>(key);
    u32 ret = 0, g;
    for (int i = 0; i < len; i++) {
        ret = (ret << 4) + p[i];
        g = ret & 0xf0000000L;
        if (g) {
            ret ^= g >> 24;
        }
        ret &= ~g;
    }
    return ret % MOD;
}

bool decrypt(char* src, int srcLen, char* targ, int targLen) {
    if (srcLen < targLen || (srcLen - targLen) % 3 != 0) {
        return false;
    }

    if (srcLen == targLen) {
        for (int i = 0; i < srcLen; i++) {
            if (src[i] != targ[i]) {
                return false;
            }
        }
        return true;
    }

    u32 h = elfHash(src, srcLen);
    if (hashTable[h]) {
        return false;
    }
    hashTable[h] = true;

    vector<int> cPos, oPos, wPos, pos;
    for (int i = 0; i < srcLen; i++) {
        if (src[i] == 'C') {
            cPos.push_back(i);
            pos.push_back(i);
        } else if (src[i] == 'O') {
            oPos.push_back(i);
            pos.push_back(i);
        } else if (src[i] == 'W') {
            wPos.push_back(i);
            pos.push_back(i);
        }
    }

    if (cPos.empty() || oPos.empty() || wPos.empty()
            || srcLen - pos.size() != targLen
            || oPos[0] < cPos[0] || wPos[0] < cPos[0]
            || cPos[cPos.size() - 1] > wPos[wPos.size() - 1]
            || oPos[oPos.size() - 1] > wPos[wPos.size() - 1]) {
        return false;
    }
    for (int i = 0; i < cPos[0]; i++) {
        if (src[i] != targ[i]) {
            return false;
        }
    }

    pos.push_back(srcLen);
    char substr[srcLen];
    //cout << srcLen << '\n';
    //cout << src << '\n';
    for (int i = 0; i < pos.size(); i++) {
        int start = (i == 0 ? 0 : pos[i - 1] + 1);
        if (pos[i] > pos[i - 1] + 1) {
            for (int j = start; j < pos[i]; j++) {
                substr[j - start] = src[j];
            }
            substr[pos[i] - start] = '\0';
            //cout << substr << '\n';
            if (!strstr(src, substr)) {
                return false;
            }
        }
    }
    //cout << "\n";

    for (int i = 0; i < cPos.size(); i++) {
        for (int j = 0; j < oPos.size(); j++) {
            for (int k = 0; k < wPos.size(); k++) {
                if (cPos[i] < oPos[j] && oPos[j] < wPos[k]) {
                    //cout << cPos[i] << ' ' << oPos[j] << ' ' << wPos[k] << '\n';
                    char newSrc[srcLen - 2];
                    for (int m = 0; m < cPos[i]; m++) {
                        //cout << m << ' ' << m << '\n';
                        newSrc[m] = src[m];
                    }
                    for (int m = oPos[j] + 1; m < wPos[k]; m++) {
                        //cout << m << ' ' << cPos[i] + m - oPos[j] - 1 << '\n';
                        newSrc[cPos[i] + m - oPos[j] - 1] = src[m];
                    }

                    for (int m = cPos[i] + 1; m < oPos[j]; m++) {
                        //cout << m << ' ' << wPos[k] - oPos[j] + m - 2 << '\n';
                        newSrc[wPos[k] - oPos[j] + m - 2] = src[m];
                    }
                    for (int m = wPos[k] + 1; m < srcLen; m++) {
                        //cout << m << ' ' << m - 3 << '\n';
                        newSrc[m - 3] = src[m];
                    }
                    newSrc[srcLen - 3] = '\0';
                    //cout << newSrc << '\n';
                    if (decrypt(newSrc, srcLen - 3, targ, targLen)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    ifstream fin("cryptcow.in");
    ofstream fout("cryptcow.out");
    string targS = "Begin the Escape execution at the Break of Dawn";
    string srcS;
    getline(fin, srcS);
    char targ[targS.size() + 1];
    for (int i = 0; i < targS.size(); i++) {
        targ[i] = targS.at(i);
    }
    targ[targS.size()] = '\0';
    char src[srcS.size() + 1];
    for (int i = 0; i < srcS.size(); i++) {
        src[i] = srcS.at(i);
    }
    src[srcS.size()] = '\0';
    bool reached = decrypt(src, srcS.size(), targ, targS.size());
    if (reached) {
        fout << "1 " << (reached ? (srcS.size() - targS.size()) / 3 : 0) << '\n';
    } else {
        fout << "0 0\n";
    }
    return 0;
}
