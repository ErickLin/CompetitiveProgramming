// 569B
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), count(100001);
    set<int> numNeed;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        count[a[i]]++;
    } 
    for (int i = 1; i <= n; i++) {
        if (!count[i]) {
            numNeed.insert(i);
        }
    }
    vector<bool> covered(100001);
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        if (!numNeed.empty() && (covered[a[i]] || a[i] > n)) {
            int first = *numNeed.begin();
            cout << first;
            covered[first] = true;
            numNeed.erase(first);
            count[a[i]]--;
            if (!count[a[i]]) {
                numNeed.insert(a[i]);
            }
        } else {
            cout << a[i];
            covered[a[i]] = true;
        }
    }
    cout << '\n';
    return 0;
}
