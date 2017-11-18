#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<vi > vvi;
typedef vector<si > vsi;
typedef vector<bool> vb;

class FiringEmployees {

    public:
        int fire(vector <int> manager, vector <int> salary, vector <int> productivity) {
            int n = manager.size() + 1;
            vsi subs(n);
            for (int i = 0; i < n - 1; i++) {
                subs[manager[i]].insert(i + 1);
            }
            fire(0, manager, subs, salary, productivity);
            vi dp(n);
            calc(0, subs, salary, productivity, dp);
            return dp[0];
        }

        void calc(int i, vsi &subs, vi &salary, vi &productivity, vi &dp) {
            int profit = 0;
            if (i > 0) {
                profit += productivity[i - 1] - salary[i - 1];
            }
            for (auto it = subs[i].begin(); it != subs[i].end(); it++) {
                calc(*it, subs, salary, productivity, dp);
                profit += dp[*it];
            }
            dp[i] = profit;
        }

        void fire(int i, vi &manager, vsi &subs, vi &salary, vi &productivity) {
            vi remove;
            for (auto it = subs[i].begin(); it != subs[i].end(); it++) {
                if (subs[*it].empty()) {
                    if (salary[*it - 1] - productivity[*it - 1] < 0) {
                        remove.push_back(*it);
                    }
                } else {
                    fire(*it, manager, subs, salary, productivity);
                }
            }
            for (int i = 0; i < remove.size(); i++) {
                subs[i].erase(remove[i]);
            }
        }
};

int main() {
    FiringEmployees a;
    cout << a.fire({0,0,0}, {1,2,3}, {3,2,1}) << '\n';
    cout << a.fire({0,1,2,3}, {4,3,2,1}, {2,3,4,5}) << '\n';
    cout << a.fire({0,1}, {1,10}, {5,5}) << '\n';
    cout << a.fire({0,1,2,1,2,3,4,2,3}, {5,3,6,8,4,2,4,6,7}, {2,5,7,8,5,3,5,7,9}) << '\n';
    cout << a.fire({0,0,1,1,2,2}, {1,1,1,2,2,2}, {2,2,2,1,1,1}) << '\n';
}
