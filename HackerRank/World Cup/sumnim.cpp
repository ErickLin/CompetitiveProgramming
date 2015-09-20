#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;

bool isWin(vector<int> &game) {
    int nimSum = 0;
    for (int i = 0; i < game.size(); i++) {
        nimSum ^= game[i];
    }
    return !nimSum;
}

void enumerate(vector<int> &game, set<vector<int> > &win, set<vector<int> > &lose) {
    if (win.find(game) != win.end() || lose.find(game) != lose.end()) {
        return;
    }
    if (isWin(game)) {
        win.insert(game);
    } else {
        lose.insert(game);
    }
    /*
    for (auto i = game.begin(); i != game.end(); i++) {
        cout << *i << ' ';
    }
    cout << '\n';
    */
    for (int i = 0; i < game.size() - 1; i++) {
        if (game[i] != 0 && game[i + 1] != 0) {
            int first = game[i];
            int second = game[i + 1];
            int sum = first + second;
            game[i] = 0;
            game[i + 1] = sum;
            enumerate(game, win, lose);
            game[i] = first;
            game[i + 1] = second;
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    set<vector<int> > win;
    set<vector<int> > lose;
    enumerate(a, win, lose);
    cout << win.size() << '\n';
    return 0;
}
