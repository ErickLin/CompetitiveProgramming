// 570A
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int maxCities = -1;
    int winningCand = -1;
    vector<int> cities(n);
    for (int i = 0; i < m; i++) {
        int maxVotes = -1;
        int bestCand = -1;
        for (int j = 0; j < n; j++) {
            int c;
            cin >> c;
            if (c > maxVotes) {
                maxVotes = c;
                bestCand = j;
            }
        }
        cities[bestCand]++;
        if (cities[bestCand] > maxCities || (cities[bestCand] == maxCities
                && bestCand < winningCand)) {
            maxCities = cities[bestCand];
            winningCand = bestCand;
        }
    }
    cout << winningCand + 1 << '\n';
    return 0;
}
