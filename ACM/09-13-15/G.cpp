#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int getValue(char c) {
    if (c >= '2' && c <= '9') {
        return c - '0';
    } else if (c == 'T' || c == 'K' || c == 'Q' || c == 'J') {
        return 10;
    } else {
        return 0;
    }
}

/*
bool canWin(string s, int playerScore, int dealerScore, int i) {
    if (playerscore > 21) {
        return false;
    }
    if (i == 0 || i == 2) {
        if (s.at(i) == 'A') {
            return canWin(s, playerScore + 11, dealerScore, i + 1)
                || canWin(s, playerScore + 1, dealerScore, i + 1);
        } else {
            return canWin(s, playerScore + getValue(s.at(i)), dealerScore, i+ 1);
        }
    } else if (i == 1 || i == 3) {
        if (s.at(i) == 'A') {
            return canWin(s, playerScore, dealerScore + 11 > 21 ? dealerScore + 1 ? dealerScore + 11, i + 1);
        } else {
            return canWin(s, playerScore, dealerScore + getValue(s.at(i)), i + 1);
        }
    } else {
        if (s.at(i) == 'A') {
            return canWin(s, playerScore + 11, dealerScore, i + 1);
                || canWin(s, playerScore + 1, dealerScore, i + 1);
        } else {
            bool cont = true;
            for (int j = i; j < s.size() && cont; j++) {
                if (s.at(j) == 'A') {
                    if (dealerScore + 11 <= 21) {
                        dealerScore += 11;
                    } else if (dealerScore + 1 <= 21) {
                        dealerScore++;
                    } else {
                        cont = false;
                    }
                }
                if (dealerScore + s.at(j) <= 21) {
*/

int main() {
    string s = "";
    while (s != "JOKER") {
        cin >> s;
        if (s != "JOKER") {
            bool canWin = false;
            int pScore = 0, dScore = 0, pAces = 0, dAces = 0;
            for (int i = 0; i < 4; i += 2) {
                if (s.at(i) == 'A') {
                    pAces++;
                } else {
                    pScore += getValue(s.at(i));
                }
            }
            for (int i = 1; i < 4; i += 2) {
                if (s.at(i) == 'A') {
                    dAces++;
                } else {
                    dScore += getValue(s.at(i));
                }
            }
            vector<int> prefix(s.size());
            vector<int> prefixAces(s.size());
            for (int i = 4; i < s.size(); i++) {
                prefix[i] = prefix[i - 1];
                prefixAces[i] = prefixAces[i - 1];
                if (s.at(i) == 'A') {
                    prefixAces[i]++;
                } else {
                    prefix[i] += getValue(s.at(i));
                }
            }
            //sep is index of player's last drawn card
            for (int sep = 3; sep < s.size() && !canWin; sep++) {
                int pAcesF = pAces + prefixAces[sep];
                int pScoreF = pScore + prefix[sep] + pAcesF;
                while (pAcesF > 0 && pScoreF + 10 <= 21) {
                    pAcesF--;
                    pScoreF += 10;
                }
                if (pScoreF <= 21) {
                    /*
                    int dScoreF = dScore + 11 * dAces;
                    if (dScoreF > 21) {
                        canWin = true;
                    }
                    for (int i = sep + 1; i < s.size() && dScoreF < 17 && !canWin; i++) {
                        if (s.at(i) == 'A') {
                            dScoreF += (dScoreF + 11 <= 21 ? 11 : 1);
                        } else {
                            dScoreF += getValue(s.at(i));
                        }
                    }
                    if (dScoreF > 21 || pScoreF >= dScoreF) {
                        canWin = true;
                    }
                    */
                    bool canDealerWin = false;
                    for (int sep2 = sep; sep2 < s.size() && !canDealerWin; sep2++) {
                        int dAcesF = dAces + prefixAces[sep2] - prefixAces[sep];
                        int dScoreF = dScore + prefix[sep2] - prefix[sep] + dAcesF;
                        while (dAcesF > 0 && dScoreF + 10 <= 21) {
                            dAcesF--;
                            dScoreF += 10;
                        }
                        //cout << sep << ' ' << pScoreF << ' ' << sep2 << ' ' << dScoreF << '\n';
                        /*
                        if ((sep2 > sep && dScoreF > 21 && s.at(sep2) != 'A' && dScoreF - getValue(s.at(sep2)) < 17)
                                || ((dScoreF >= 17 || sep2 == s.size() - 1) && pScoreF >= dScoreF)) {
                            canWin = true;
                        }
                        */
                        if (dScoreF >= 17 && dScoreF <= 21 && dScoreF > pScoreF) {
                            canDealerWin = true;
                        }
                    }
                    if (!canDealerWin) {
                        canWin = true;
                    }
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
