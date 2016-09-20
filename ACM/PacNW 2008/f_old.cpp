#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Data set " << i << ": ";
        int k;
        cin >> k;
        vi ts(k);
        map<int, vector<char> > labels;
        for (int j = 0; j < k; j++) {
            cin >> ts[j];
            labels[ts[j]].push_back('A' + j);
        }
        for (auto it = labels.begin(); it != labels.end(); it++) {
            sort(it->second.rbegin(), it->second.rend());
            /*
            cout << it->first << ": ";
            for (int j = 0; j < it->second.size(); j++) {
                cout << it->second[j] << ' ';
            }
            cout << '\n';
            */
        }
        //cout << '\n';
        sort(ts.begin(), ts.end());
        int a = 0, b = 0, c = 0, numSolved = 0, penalty = 0;
        for (int j = 0; j < k; j++) {
            int* argmin;
            if (min(min(a, b), c) == a) {
                argmin = &a;
            } else if (min(min(a, b), c) == b) {
                argmin = &b;
            } else {
                argmin = &c;
            }
            if (*argmin + ts[j] <= 300) {
                *argmin += ts[j];
                numSolved++;
                penalty += *argmin;
                char label = labels[ts[j]].back();
                labels[ts[j]].pop_back();
                cout << label << ' ';
            }
        }
        cout << numSolved << ' ' << penalty << '\n';
    }
    return 0;
}
