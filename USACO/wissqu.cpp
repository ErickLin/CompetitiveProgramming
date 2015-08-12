/*
ID: Jugglebrosjr2
LANG: C++
TASK: wissqu
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

typedef vector<vector<int> > pasture;
typedef pair<int, pair<int, int> > move;
//set<vector<move> > finalMoves;
vector<move> movesAns;
int numArrang = 0;

void updateNumNear(vector<vector<vector<int> > > &near, pasture &herds
        , int newHerdNum, int i, int j) {
    vector<pair<int, int> > adj(9);
    adj[0] = make_pair(i, j);
    adj[1] = make_pair(i - 1, j - 1);
    adj[2] = make_pair(i, j - 1);
    adj[3] = make_pair(i - 1, j);
    adj[4] = make_pair(i - 1, j + 1);
    adj[5] = make_pair(i, j + 1);
    adj[6] = make_pair(i + 1, j + 1);
    adj[7] = make_pair(i + 1, j);
    adj[8] = make_pair(i + 1, j - 1);
    for (int k = 0; k < 9; k++) {
        if (adj[k].first >= 0 && adj[k].first < 4
                && adj[k].second >= 0 && adj[k].second < 4) {
            near[herds[i][j]][adj[k].first][adj[k].second]--;
            near[newHerdNum][adj[k].first][adj[k].second]++;
        }
    }
}

void place(pasture &herds, vector<int> &left, vector<vector<vector<int> > > &near
        , vector<vector<bool> > &vis, vector<move> &moves) {
    bool done = true;
    for (int k = 0; k < left.size(); k++) {
        if (left[k]) {
            done = false;
        }
    }
    if (done) {
        //finalMoves.insert(moves);
        if (!numArrang) {
            movesAns = moves;
        }
        numArrang++;
    } else for (int k = 0; k < left.size(); k++) {
        if (left[k]) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (!vis[i][j] && near[k][i][j] == 0) {
                        updateNumNear(near, herds, k, i, j);
                        int temp = herds[i][j];
                        herds[i][j] = k;
                        left[k]--;
                        vis[i][j] = true;
                        moves.push_back(make_pair(k, make_pair(i, j)));

                        place(herds, left, near, vis, moves);

                        updateNumNear(near, herds, temp, i, j);
                        herds[i][j] = temp;
                        left[k]++;
                        vis[i][j] = false;
                        moves.pop_back();
                    }
                }
            }
        }
    }
}

int main() {
    ifstream fin("wissqu.in");
    ofstream fout("wissqu.out");
    pasture herds(4, vector<int>(4));
    vector<vector<vector<int> > > near(5, vector<vector<int> >(4, vector<int>(4)));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char c;
            fin >> c;
            herds[i][j] = c - 'A';
            vector<pair<int, int> > adj(9);
            adj[0] = make_pair(i, j);
            adj[1] = make_pair(i - 1, j - 1);
            adj[2] = make_pair(i, j - 1);
            adj[3] = make_pair(i - 1, j);
            adj[4] = make_pair(i - 1, j + 1);
            adj[5] = make_pair(i, j + 1);
            adj[6] = make_pair(i + 1, j + 1);
            adj[7] = make_pair(i + 1, j);
            adj[8] = make_pair(i + 1, j - 1);
            for (int k = 0; k < 9; k++) {
                if (adj[k].first >= 0 && adj[k].first < 4
                        && adj[k].second >= 0 && adj[k].second < 4) {
                    near[herds[i][j]][adj[k].first][adj[k].second]++;
                }
            }
        }
    }
    //number of members of new herd that need to be placed
    vector<int> left(5);
    left[0] = 3;
    left[1] = 3;
    left[2] = 3;
    left[3] = 4;
    left[4] = 3;
    //start by placing a 'D'/3 herd
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (near[3][i][j] == 0) {
                updateNumNear(near, herds, 3, i, j);
                int temp = herds[i][j];
                herds[i][j] = 3;
                left[3]--;
                vector<vector<bool> > vis(4, vector<bool>(4));
                vis[i][j] = true;
                vector<move> moves;
                moves.push_back(make_pair(3, make_pair(i, j)));

                place(herds, left, near, vis, moves);

                updateNumNear(near, herds, temp, i, j);
                herds[i][j] = temp;
                left[3]++;
                vis[i][j] = false;
                moves.pop_back();
            }
        }
    }
    //vector<move> movesAns = *finalMoves.begin();
    for (int i = 0; i < movesAns.size(); i++) {
        fout << (char) ('A' + movesAns[i].first) << ' ' << 1 + movesAns[i].second.first
            << ' ' << 1 + movesAns[i].second.second << '\n';
    }
    //fout << finalMoves.size() << '\n';
    fout << numArrang << '\n';
    return 0;
}
