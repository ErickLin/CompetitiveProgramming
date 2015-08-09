/*
ID: Jugglebrosjr2
LANG: C++
TASK: fence8
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

/*
struct cmp {
    bool operator()(const int &a, const int &b) {
        return a > b;
    }
};

bool cmp2(const int &a, const int &b) {
    return a > b;
}
*/

bool canReach(int boardNum, int amtUsed, vector<int> &boards, int railsLeft
        , int lastUsed, vector<int> &railsNeeded, int discarded, int maxDiscard) {
    if (railsLeft == 0) {
        return true;
    }
    //Start with the last rail length used for the current board, or the
    //highest rail length if this is the first rail used for the board
    for (int railLen = lastUsed; railLen >= 0; railLen--) {
        if (railsNeeded[railLen] > 0) {
            if (amtUsed + railLen <= boards[boardNum]) {
                railsNeeded[railLen]--;
                if (canReach(boardNum, amtUsed + railLen, boards, railsLeft - 1
                        , railLen, railsNeeded, discarded, maxDiscard)) {
                    return true;
                }
                railsNeeded[railLen]++;
            }
        }
    }
    //Move to the next board, discarding the remainder of the current board
    //as long as the amount discarded is less than the maximum possible
    if (discarded + boards[boardNum] - amtUsed <= maxDiscard
            && boardNum + 1 < boards.size()) {
        if (canReach(boardNum + 1, 0, boards, railsLeft, railsNeeded.size() - 1
                , railsNeeded
                , discarded + boards[boardNum] - amtUsed, maxDiscard)) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("fence8.in");
    ofstream fout("fence8.out");
    int n, r;
    fin >> n;
    vector<int> boards(n);
    int boardsTotal = 0;
    for (int i = 0; i < n; i++) {
        fin >> boards[i];
        boardsTotal += boards[i];
    }
    sort(boards.begin(), boards.end());
    fin >> r;
    vector<int> rails(r);
    int railsMax = 0;
    for (int i = 0; i < r; i++) {
        fin >> rails[i];
        railsMax = max(railsMax, rails[i]);
    }
    sort(rails.begin(), rails.end());
    int ans = 0;
    int lo = 1, hi = r;
    while (lo <= hi) {
        int mid = lo + ((hi - lo) >> 1);
        vector<int> railsNeeded(railsMax + 1);
        int railsTotal = 0;
        for (int i = 0; i < mid; i++) {
            railsNeeded[rails[i]]++;
            railsTotal += rails[i];
        }
        int maxDiscard = boardsTotal - railsTotal;
        if (maxDiscard >= 0 && canReach(0, 0, boards, mid, railsMax, railsNeeded, 0, maxDiscard)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    fout << ans << '\n';
    return 0;
}
