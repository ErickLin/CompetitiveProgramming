#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    stack<pair<int, int> > stk;
    int n;
    cin >> n;
    vector<int> p(n);
    int maxDays = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        if (stk.empty()) {
            stk.push(make_pair(p[i], 0));
        } else {
            pair<int, int> elem = stk.top();
            if (p[i] > elem.first) {
                stk.push(make_pair(p[i], 1));
                maxDays = max(maxDays, 1);
            } else {
                int days = elem.second;
                while (!stk.empty() && p[i] <= elem.first) {
                    stk.pop();
                    if (!stk.empty()) {
                        days = max(days, elem.second);
                        elem = stk.top();
                    }
                }
                if (stk.empty()) {
                    stk.push(make_pair(p[i], 0));
                } else {
                    stk.push(make_pair(p[i], days + 1));
                    maxDays = max(maxDays, days + 1);
                }
            }
        }
    }
    cout << maxDays << '\n';
    return 0;
}