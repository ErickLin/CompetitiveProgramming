/*
ID: Jugglebrosjr2
LANG: C++
TASK: theme
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    ifstream fin("theme.in");
    ofstream fout("theme.out");
    int n;
    fin >> n;
    if (n < 10) {
        fout << "0\n";
        return 0;
    }
    vector<int> notes(n);
    vector<int> d(n - 1);
    for (int i = 0; i < n; i++) {
        fin >> notes[i];
        if (i > 0) {
            d[i - 1] = notes[i] - notes[i - 1];
        }
    }
    int maxLen = -1;
    //theme must be at least five notes long
    int lo = 4, hi = (d.size() >> 1);
    //do binary search over lengths of sequences of pitch changes
    while (lo <= hi) {
        int mid = lo + ((hi - lo) >> 1);
        //maps each theme to the indices of its first and last occurrences
        map<vector<int>, pair<int, int> > themeIndices;
        for (int i = 0; i <= d.size() - mid && maxLen < mid; i++) {
            vector<int> theme(mid);
            for (int j = 0; j < mid; j++) {
                theme[j] = d[i + j];
            }
            if (themeIndices.find(theme) == themeIndices.end()) {
                themeIndices[theme] = make_pair(i, i);
            } else {
                pair<int, int> indices = themeIndices[theme];
                if (i < indices.first) {
                    themeIndices[theme].first = i;
                }
                if (i > indices.second) {
                    themeIndices[theme].second = i;
                }
                indices = themeIndices[theme];
                //check that subsequences of notes, not differences
                //(hence the extra 1), are disjoint
                if (indices.second - indices.first - 1 >= mid) {
                    maxLen = mid;
                }
            }
        }
        if (maxLen == mid) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    fout << maxLen + 1 << '\n';
    return 0;
}
