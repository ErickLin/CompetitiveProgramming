/*
ID: Jugglebrosjr2
LANG: C++
TASK: rectbarn
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    }
};

int main() {
    ifstream fin("rectbarn.in");
    ofstream fout("rectbarn.out");
    int r, c, p;
    fin >> r >> c >> p;
    set<pair<int, int>, cmp> damaged;
    for (int i = 0; i < p; i++) {
        int a, b;
        fin >> a >> b;
        damaged.insert(make_pair(--a, --b));
    }
    int ans = 0;
    /*
    //Prioritizes height over width
    vector<vector<pair<int, int> > > dpVert(r, vector<pair<int, int> >(c));
    //Prioritizes width over height
    vector<vector<pair<int, int> > > dpHor(r, vector<pair<int, int> >(c));
    for (int i = 0; i < r; i++) {
        dpVert[i][0] = dpHor[i][0] = make_pair(
                damaged[i][0] ? 0 : (i > 0 ? dpVert[i - 1][0].first + 1 : 1),
                damaged[i][0] ? 0 : 1);
        if (dpVert[i][0].first * dpVert[i][0].second > ans) {
            ans = dpVert[i][0].first * dpVert[i][0].second;
        }
        //cout << dpVert[i][0].first << ' ' << dpVert[i][0].second << '\n';
    }
    for (int j = 0; j < c; j++) {
        dpVert[0][j] = dpHor[0][j] = make_pair(
                damaged[0][j] ? 0 : 1,
                damaged[0][j] ? 0 : (j > 0 ? dpVert[0][j - 1].second + 1 : 1));
        if (dpVert[0][j].first * dpVert[0][j].second > ans) {
            ans = dpVert[0][j].first * dpVert[0][j].second;
        }
        //cout << dpVert[0][j].first << ' ' << dpVert[0][j].second << '\n';
    }
    for (int i = 1; i < r; i++) {
        for (int j = 1; j < c; j++) {
            if (damaged[i][j]) {
                dpVert[i][j].first = 0;
                dpVert[i][j].second = 0;
                dpHor[i][j].first = 0;
                dpHor[i][j].second = 0;
            } else {
                if (damaged[i - 1][j - 1]) {
                    dpVert[i][j].second = 1;
                    dpHor[i][j].first = 1;
                } else {
                    dpVert[i][j].second = dpVert[i][j - 1].second + 1;
                    dpHor[i][j].first = dpHor[i - 1][j].first + 1;
                }
                dpVert[i][j].first = dpVert[i - 1][j].first + 1;
                dpHor[i][j].second = dpHor[i][j - 1].second + 1;
            }
            if (dpVert[i][j].first * dpVert[i][j].second > ans) {
                ans = dpVert[i][j].first * dpVert[i][j].second;
            }
            if (dpHor[i][j].first * dpHor[i][j].second > ans) {
                ans = dpHor[i][j].first * dpHor[i][j].second;
            }
            cout << dpVert[i][j].first << ' ' << dpVert[i][j].second << ' '
                << dpHor[i][j].first << ' ' << dpHor[i][j].second << '\n';
        }
        cout << '\n';
    }
    */
    set<pair<int, int>, cmp>::iterator it = damaged.begin();
    vector<int> maxLen(r);
    for (int j = 0; j < c; j++) {
        //compute "histogram" for current column
        for (int i = 0; i < r; i++) {
            if (i == it->first && j == it->second) {
                maxLen[i] = 0;
                it++;
            } else {
                maxLen[i]++;
            }
            //cout << maxLen[i] << ' ';
        }
        //cout << '\n';
        //each element stores its position and the position of its starting rectangle
        stack<pair<int, int> > s;
        int rectStart = 0;
        for (int i = 0; i < r; i++) {
            int currentW = maxLen[i];
            //cout << "j:" << j << " i:" << i << '\n';
            if (s.empty()) {
                rectStart = i;
                s.push(make_pair(i, rectStart));
            } else {
                int otherW = maxLen[s.top().first];
                if (currentW > otherW) {
                    rectStart = i;
                    s.push(make_pair(i, rectStart));
                } else if (currentW < otherW) {
                    do {
                        int start = s.top().second;
                        int end = i;
                        ans = max(ans, (end - start) * otherW);
                        s.pop();
                        rectStart = start;
                        if (!s.empty()) {
                            otherW = maxLen[s.top().first];
                        }
                    } while (!s.empty() && currentW < otherW);
                    s.push(make_pair(i, rectStart));
                }
            }
        }
        while (!s.empty()) {
            int start = s.top().second;
            int end = r;
            int width = maxLen[s.top().first];
            //cout << start << "->" << end << ": " << width << '\n';
            ans = max(ans, (end - start) * width);
            s.pop();
        } 
    }
    fout << ans << '\n';
    return 0;
}
