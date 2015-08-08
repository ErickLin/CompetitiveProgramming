/*
ID: Jugglebrosjr2
LANG: C++
TASK: rect1
*/
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;
typedef pair<int, int> point;
typedef pair<point, point> window;

int main() {
    ifstream fin("rect1.in");
    ofstream fout("rect1.out");
    map<int, window> windows;
    map<int, int> depth;
    int a, b, n;
    fin >> a >> b >> n;
    vector<int> colorCount(2501);
    windows[1 * 2501 + colorCount[1]++]
        = make_pair(make_pair(0, 0), make_pair(a, b));
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2, id;
        fin >> x1 >> y1 >> x2 >> y2 >> id;
        id = id * 2501 + colorCount[id]++;
        windows[id] = make_pair(make_pair(min(x1, x2), min(y1, y2))
                , make_pair(max(x1, x2), max(y1, y2)));
        depth[id] = -1 * (i + 1);
    }
    vector<int> areaCount(2501);
    for (map<int, window>::iterator out = windows.begin(); out != windows.end(); out++) {
        int id = out->first;
        set<window> partitions;
        partitions.insert(windows[id]);
        for (map<int, window>::iterator it = windows.begin()
                ; it != windows.end()
                ; it++) {
            int idOther = it->first;
            if (depth[idOther] < depth[id]) {
                int x1Other = windows[idOther].first.first;
                int y1Other = windows[idOther].first.second;
                int x2Other = windows[idOther].second.first;
                int y2Other = windows[idOther].second.second;
                set<window> add;
                set<window> remove;
                for (set<window>::iterator pt = partitions.begin()
                        ; pt != partitions.end()
                        ; pt++) {
                    int x1 = pt->first.first, y1 = pt->first.second
                        , x2 = pt->second.first, y2 = pt->second.second;
                    //break partition into at most 4 new pieces that
                    //are not covered by the current window "other"
                    if (y1 < y2Other && y2 > y1Other) {
                        if (x1 < x1Other && x2 > x1Other) {
                            add.insert(make_pair(make_pair(x1, y1)
                                        , make_pair(x1Other, y2)));
                        }
                        if (x2 > x2Other && x1 < x2Other) {
                            add.insert(make_pair(make_pair(x2Other, y1)
                                        , make_pair(x2, y2)));
                        }
                    }
                    if (x1 < x2Other && x2 > x1Other) {
                        if (y1 < y1Other && y2 > y1Other) {
                            add.insert(make_pair(make_pair(max(x1Other, x1), y1)
                                        , make_pair(min(x2Other, x2), y1Other)));
                        }
                        if (y2 > y2Other && y1 < y2Other) {
                            add.insert(make_pair(make_pair(max(x1Other, x1), y2Other)
                                        , make_pair(min(x2Other, x2), y2)));
                        }
                    }
                    if (y1 < y2Other && y2 > y1Other
                            && x1 < x2Other && x2 > x1Other) {
                        remove.insert(*pt);
                    }
                }
                for (set<window>::iterator pt = add.begin()
                        ; pt != add.end()
                        ; pt++) {
                    partitions.insert(*pt);
                }
                for (set<window>::iterator pt = remove.begin()
                        ; pt != remove.end()
                        ; pt++) {
                    partitions.erase(*pt);
                }
            }
        }
        int areaVisible = 0;
        for (set<window>::iterator it = partitions.begin()
                ; it != partitions.end()
                ; it++) {
            areaVisible += (it->second.first - it->first.first)
                * (it->second.second - it->first.second);
        }
        id /= 2501;
        areaCount[id] += areaVisible;
    }
    for (int i = 1; i <= 2500; i++) {
        if (areaCount[i] > 0) {
            fout << i << ' ' << areaCount[i] << '\n';
        }
    }
    return 0;
}
