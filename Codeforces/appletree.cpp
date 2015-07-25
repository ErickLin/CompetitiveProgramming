#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int cmpL(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

int cmpR(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int> > l, r;
    for (int i = 0; i < n; i++) {
        int x, a;
        cin >> x >> a;
        if (x > 0) {
            r.push_back(make_pair(x, a));
        } else {
            l.push_back(make_pair(x, a));
        }
    }
    sort(l.begin(), l.end(), cmpL);
    sort(r.begin(), r.end(), cmpR);
    int sum = 0;
    if (l.size() < r.size()) {
        for (int i = 0; i < l.size(); i++) {
            sum += l[i].second;
            sum += r[i].second;
        }
        sum += r[l.size()].second;
    } else if (l.size() > r.size()) {
        for (int i = 0; i < r.size(); i++) {
            sum += l[i].second;
            sum += r[i].second;
        }
        sum += l[r.size()].second;
    } else {
        for (int i = 0; i < l.size(); i++) {
            sum += l[i].second;
            sum += r[i].second;
        }
    }
    cout << sum << '\n';
    return 0;
}
