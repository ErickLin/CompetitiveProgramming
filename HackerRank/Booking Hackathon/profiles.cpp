#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct hotel {
    int id;
    int price;
    set<string> facilities;
};

int main() {
    string line;
    getline(cin, line);
    int n = stoi(line);
    vector<hotel> hotels(n);
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        string s;
        int pos = 0;
        while (line[pos] != ' ') {
            s += line[pos];
            pos++;
        }
        int id = stoi(s);
        s = "";
        pos++;
        while (line[pos] != ' ') {
            s += line[pos];
            pos++;
        }
        int price = stoi(s);
        s = "";
        pos++;
        set<string> facilities;
        while (pos < line.size()) {
            if (line[pos] == ' ') {
                facilities.insert(s);
                s = "";
            } else {
                s += line[pos];
            }
            pos++;
        }
        if (s != "") {
            facilities.insert(s);
        }
        hotels[i].id = id;
        hotels[i].price = price;
        hotels[i].facilities = facilities;
    }
    getline(cin, line);
    int m = stoi(line);
    for (int i = 0; i < m; i++) {
        getline(cin, line);
        string s;
        int pos = 0;
        while (line[pos] != ' ') {
            s += line[pos];
            pos++;
        }
        int budget = stoi(s);
        s = "";
        pos++;
        vector<string> facilities;
        while (pos < line.size()) {
            if (line[pos] == ' ') {
                facilities.push_back(s);
                s = "";
            } else {
                s += line[pos];
            }
            pos++;
        }
        if (s != "") {
            facilities.push_back(s);
        }

        vector<hotel> canReach;
        for (int j = 0; j < n; j++) {
            if (hotels[j].price <= budget) {
                bool reachable = true;
                for (int i = 0; i < facilities.size() && reachable; i++) {
                    if (hotels[j].facilities.find(facilities[i]) == hotels[j].facilities.end()) {
                        reachable = false;
                    }
                }
                if (reachable) {
                    canReach.push_back(hotels[j]);
                }
            }
        }
        sort(canReach.begin(), canReach.end(), [](hotel a, hotel b) {
            if (a.facilities.size() == b.facilities.size()) {
                if (a.price == b.price) {
                    return a.id < b.id;
                }
                return a.price < b.price;
            }
            return a.facilities.size() > b.facilities.size();
        });
        if (!canReach.empty()) {
            cout << canReach[0].id;
            for (int i = 1; i < canReach.size(); i++) {
                cout << ' ' << canReach[i].id;
            }
        }
        cout << '\n';
    }
}
