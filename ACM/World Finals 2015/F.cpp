#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vp;
typedef vector<vector<pii> > vvp;
typedef pair<int, int> pos;

int main() {
    int r, c;
    cin >> r >> c;
    vector<vector<char> > keyboard(r, vector<char>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> keyboard[i][j];
        }
    }
    vector<vvp > neighbors(r, vvp(c));
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            int dy, dx;
            for (dy = -1; y + dy >= 0; dy--) {
                if (keyboard[y + dy][x] != keyboard[y][x]) {
                    neighbors[y][x].push_back(make_pair(y + dy, x));
                    break;
                }
            }
            for (dy = 1; y + dy < r; dy++) {
                if (keyboard[y + dy][x] != keyboard[y][x]) {
                    neighbors[y][x].push_back(make_pair(y + dy, x));
                    break;
                }
            }
            for (dx = -1; x + dx >= 0; dx--) {
                if (keyboard[y][x + dx] != keyboard[y][x]) {
                    neighbors[y][x].push_back(make_pair(y, x + dx));
                    break;
                }
            }
            for (dx = 1; x + dx < c; dx++) {
                if (keyboard[y][x + dx] != keyboard[y][x]) {
                    neighbors[y][x].push_back(make_pair(y, x + dx));
                    break;
                }
            }
        }
    }
    string word;
    cin >> word;
    word.append("*");
    queue<pair<pos, int> > q;
    q.push(make_pair(make_pair(0, 0), 0));
    vector<vvi > strokesAt(r, vvi(c, vi(word.size() + 1)));
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            fill(strokesAt[y][x].begin(), strokesAt[y][x].end(), -1);
        }
    }
    strokesAt[0][0][0] = 0;
    while (!q.empty()) {
        pair<pos, int> state = q.front();
        q.pop();
        int y = state.first.first;
        int x = state.first.second;
        int wordPos = state.second;
        if (wordPos == word.size()) {
            cout << strokesAt[y][x][wordPos] << '\n';
            break;
        }
        if (keyboard[y][x] == word.at(wordPos) && strokesAt[y][x][wordPos + 1] == -1) {
            strokesAt[y][x][wordPos + 1] = strokesAt[y][x][wordPos] + 1;
            q.push(make_pair(make_pair(y, x), wordPos + 1));
        }
        for (int j = 0; j < neighbors[y][x].size(); j++) {
            pair<int, int> neighbor = neighbors[y][x][j];
            if (strokesAt[neighbor.first][neighbor.second][wordPos] == -1) {
                strokesAt[neighbor.first][neighbor.second][wordPos] = strokesAt[y][x][wordPos] + 1;
                q.push(make_pair(make_pair(neighbor.first, neighbor.second), wordPos));
            }
        }
    }
}
