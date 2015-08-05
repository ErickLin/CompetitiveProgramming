/*
ID: Jugglebrosjr2
LANG: C++
TASK: charrec
*/
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

vector<vector<int> > getImgsTruth(vector<char> &letters) {
    ifstream fin("font.in");
    int n;
    fin >> n;
    vector<vector<int> > imgs(27);
    for (int l = 0; l < letters.size(); l++) {
        vector<int> img(20);
        for (int i = 0; i < 20; i++) {
            int row = 0;
            for (int j = 0; j < 20; j++) {
                char c;
                fin >> c;
                if (c == '1') {
                    row |= (1 << j);
                }
            }
            img[i] = row;
        }
        imgs[l] = img;
    }
    return imgs;
}

vector<int> getImgsTest() {
    ifstream fin("charrec.in");
    int n;
    fin >> n;
    vector<int> imgsTest(n);
    for (int i = 0; i < n; i++) {
        int row = 0;
        for (int j = 0; j < 20; j++) {
            char c;
            fin >> c;
            if (c == '1') {
                row |= (1 << j);
            }
        }
        imgsTest[i] = row;
    }
    return imgsTest;
}

int main() {
    vector<char> letters(27);
    letters[0] = ' ';
    for (int i = 1; i <= 26; i++) {
        letters[i] = 'a' + i - 1;
    }
    vector<vector<int> > imgsTruth = getImgsTruth(letters);
    vector<int> imgsTest = getImgsTest();
    vector<vector<vector<int> > > diffs(imgsTest.size(),
            vector<vector<int> >(27, vector<int>(20)));
    for (int i = 0; i < imgsTest.size(); i++) {
        for (int j = 0; j < letters.size(); j++) {
            for (int k = 0; k < 20; k++) {
                diffs[i][j][k] = __builtin_popcount(imgsTest[i] ^ imgsTruth[j][k]);
            }
        }
    }
    const int thres = 120;
    //Min number of corruptions it takes to get an answer ending at index
    vector<int> dp(imgsTest.size());
    fill(dp.begin(), dp.end(), INT_MAX);
    //Best character ending at index
    vector<char> ans(imgsTest.size());
    fill(ans.begin(), ans.end(), '?');
    //Ending index of previous character according to best answer at index
    vector<int> prev(imgsTest.size());
    fill(prev.begin(), prev.end(), -1);

    //Start with the first letter, which can end at index 18, 19, or 20
    //case 1: no line duplicated or missing
    if (imgsTest.size() >= 20) {
        for (int l = 0; l < letters.size(); l++) {
            int cost = 0;
            for (int k = 0; k < 20; k++) {
                cost += diffs[k][l][k];
            }
            if (cost < dp[19] && cost <= 120) {
                dp[19] = cost;
                ans[19] = letters[l];
            }
        }
    }
    //case 2: one line duplicated
    if (imgsTest.size() >= 21) {
        int minCost = thres + 1;
        char currentAns = '?';
        for (int l = 0; l < letters.size(); l++) {
            //line j is duplicated
            for (int j = 0; j < 20; j++) {
                int cost = 0;
                for (int k = 0; k < j; k++) {
                    cost += diffs[k][l][k];
                }
                cost += min(diffs[j][l][j], diffs[j + 1][l][j]);
                for (int k = j + 1; k < 20; k++) {
                    cost += diffs[k + 1][l][k];
                }
                if (cost < dp[20] && cost <= 120) {
                    dp[20] = cost;
                    ans[20] = letters[l];
                }
            }
        }
    }
    //case 3: one line missing
    if (imgsTest.size() >= 19) {
        int minCost = thres + 1;
        char currentAns = '?';
        for (int l = 0; l < letters.size(); l++) {
            //line j is deleted
            for (int j = 0; j < 20; j++) {
                int cost = 0;
                for (int k = 0; k < j; k++) {
                    cost += diffs[k][l][k];
                }
                for (int k = j + 1; k < 20; k++) {
                    cost += diffs[k - 1][l][k];
                }
                if (cost < dp[18] && cost <= 120) {
                    dp[18] = cost;
                    ans[18] = letters[l];
                }
            }
        }
    }

    //Build up solutions at all possible positions
    for (int i = 37; i < imgsTest.size(); i++) {
        //case 1: no line duplicated or missing
        //check that there is valid solution for last letter
        if (dp[i - 20] != INT_MAX) {
            for (int l = 0; l < letters.size(); l++) {
                int cost = dp[i - 20];
                for (int k = 0; k < 20; k++) {
                    cost += diffs[i - 20 + k][l][k];
                }
                if (cost < dp[i] && cost <= dp[i - 20] + 120) {
                    dp[i] = cost;
                    ans[i] = letters[l];
                    prev[i] = i - 20;
                }
            }
        }
        //case 2: one line duplicated
        if (dp[i - 21] != INT_MAX) {
            for (int l = 0; l < letters.size(); l++) {
                //line j is duplicated
                for (int j = 0; j < 20; j++) {
                    int cost = dp[i - 21];
                    for (int k = 0; k < j; k++) {
                        cost += diffs[i - 21 + k][l][k];
                    }
                    cost += min(diffs[i - 21 + j][l][j]
                            , diffs[i - 21 + j + 1][l][j]);
                    for (int k = j + 1; k < 20; k++) {
                        cost += diffs[i - 21 + k + 1][l][k];
                    }
                    if (cost < dp[i] && cost <= dp[i - 21] + 120) {
                        dp[i] = cost;
                        ans[i] = letters[l];
                        prev[i] = i - 21;
                    }
                }
            }
        }
        //case 3: one line missing
        if (dp[i - 19] != INT_MAX) {
            for (int l = 0; l < letters.size(); l++) {
                //line j is deleted
                for (int j = 0; j < 20; j++) {
                    int cost = dp[i - 19];
                    for (int k = 0; k < j; k++) {
                        cost += diffs[i - 19 + k][l][k];
                    }
                    for (int k = j + 1; k < 20; k++) {
                        cost += diffs[i - 19 + k - 1][l][k];
                    }
                    if (cost < dp[i] && cost <= dp[i - 19] + 120) {
                        dp[i] = cost;
                        ans[i] = letters[l];
                        prev[i] = i - 19;
                    }
                }
            }
        }
    }

    //Print out answer
    ofstream fout("charrec.out");
    stack<char> s;
    for (int current = imgsTest.size() - 1; current != -1; current = prev[current]) {
        s.push(ans[current]);
    }
    while (!s.empty()) {
        fout << s.top();
        s.pop();
    }
    fout << '\n';
    return 0;
}
