#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<char, int> > log(n);
    set<int> inRoom;
    set<int> init;
    for (int i = 0; i < n; i++) {
        char act;
        int id;
        cin >> act >> id;
        log[i] = make_pair(act, id);
        if (act == '+') {
            inRoom.insert(id);
        } else {
            if (inRoom.find(id) == inRoom.end()) {
                init.insert(id);
            } else {
                inRoom.erase(id);
            }
        }
    }
    inRoom = init;
    int cap = (int) inRoom.size();
    for (int i = 0; i < n; i++) {
        char act = log[i].first;
        int id = log[i].second;
        if (act == '+') {
            inRoom.insert(id);
            cap = max(cap, (int) inRoom.size());
        } else {
            inRoom.erase(id);
        }
    }
    cout << cap << '\n';
}
