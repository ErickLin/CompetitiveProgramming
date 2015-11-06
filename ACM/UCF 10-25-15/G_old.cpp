#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;

int main() {
    int n;
    cin >> n;
    vi heights(n);
    map<int, vector<int> > atHeight;
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
        atHeight[heights[i]].push_back(i);
    }
    vb popped(n);
    int arrows = 0;
    for (int i = 0; i < n; i++) {
        if (!popped[i]) {
            arrows++;
            bool popping = true;
            int x = i;
            popped[x] = true;
            while (popping) {
                /*
                int lo = 0, hi = atHeight[heights[x] - 1].end();
                while (lo <= hi) {
                    int mid = lo + ((hi - lo) >> 1);
                    if (atHeight[heights[x] - 1][mid]) {
                    }
                }
                */
                auto it = lower_bound(atHeight[heights[x] - 1].begin()
                        , atHeight[heights[x] - 1].end(), x);
                if (it == atHeight[heights[x] - 1].end()) {
                    popping = false;
                } else {
                    x = *it;
                    popped[x] = true;
                }
            }
        }
    }
    cout << arrows << '\n';
}
