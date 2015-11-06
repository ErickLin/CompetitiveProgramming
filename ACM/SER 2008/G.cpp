#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int getValue(char c) {
    if (c >= '2' && c <= '9') {
        return c - '0';
    } else if (c == 'T' || c == 'K' || c == 'Q' || c == 'J') {
        return 10;
    } else if (c == 'A') {
        return 11;
    } else {
        return 0;
    }
}

bool checkWin(int pScore, int dScore, int dAces) {
    if (dScore > 21 || pScore >= dScore) {
        return true;
    } else {
        return false;
    }
}

bool dealerPlay(string s, int pScore, int dScore, int dAces, int card) {
    for (int i = card; i < s.size() && dScore < 17; i++) {
        if (s.at(i) == 'A') {
            dAces++;
        }
        dScore += getValue(s.at(i));
        while (dScore > 21 && dAces > 0) {
            dScore -= 10;
            dAces--;
        }
    }
    return checkWin(pScore, dScore, dAces);
}

int main() {
    string s = "";
    while (s != "JOKER") {
        cin >> s;
        if (s != "JOKER") {
            int pScore = 0, pAces = 0, dScore = 0, dAces = 0;;
            for (int i = 0; i < 4; i++) {
                if (i % 2 == 1) {
                    dScore += getValue(s.at(i));
                    if (s.at(i) == 'A') {
                        dAces++;
                    }
                    while (dScore > 21 && dAces > 0) {
                        dScore -= 10;
                        dAces--;
                    }
                } else {
                    pScore += getValue(s.at(i));
                    if (s.at(i) == 'A') {
                        pAces++;
                    }
                    while (pScore > 21 && pAces > 0) {
                        pScore -= 10;
                        pAces--;
                    }
                }
            }
            bool canWin = dealerPlay(s, pScore, dScore, dAces, 4);
            for (int i = 4; i < s.size() && !canWin; i++) {
                pScore += getValue(s.at(i));
                if (s.at(i) == 'A') {
                    pAces++;
                }
                while (pScore > 21 && pAces > 0) {
                    pScore -= 10;
                    pAces--;
                }
                if (pScore <= 21) {
                    canWin = canWin || dealerPlay(s, pScore, dScore, dAces, i + 1);
                }
            }
            if (canWin) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}
