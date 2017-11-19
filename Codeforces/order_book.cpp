// 572B
#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

struct cmp {
    bool operator()(const int &a, const int &b) {
        return a > b;
    }
};

int main() {
    int n, s;
    cin >> n >> s; 
    map<int, int, cmp> buy;
    map<int, int> sell;
    for (int i = 0; i < n; i++) {
        char d;
        int p, v;
        cin >> d >> p >> v;
        if (d == 'B') {
            buy[p] += v;
        } else {
            sell[p] += v;
        }
    }
    int i = 0;
    stack<pair<int, int> > stk;
    for (map<int, int>::iterator it = sell.begin(); i < s && it != sell.end(); it++) {
        stk.push(make_pair(it->first, it->second));
        i++;
    }
    while (!stk.empty()) {
        cout << 'S' << ' ' << stk.top().first << ' ' << stk.top().second << '\n';
        stk.pop();
    }
    i = 0;
    for (map<int, int>::iterator it = buy.begin(); i < s && it != buy.end(); it++) {
        cout << 'B' << ' ' << it->first << ' ' << it->second << '\n';
        i++;
    }
    return 0;
}
