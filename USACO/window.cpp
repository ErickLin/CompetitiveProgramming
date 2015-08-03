/*
ID: Jugglebrosjr2
LANG: C++
TASK: window
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
    ifstream fin("window.in");
    ofstream fout("window.out");
    map<char, window> windows;
    map<char, int> depth;
    int topCounter = -1;
    int bottomCounter=  1;
    string line;
    while (fin >> line) {
        char id = line.at(2);
        if (line.at(0) == 'w') {
            int x1, y1, x2, y2;
            string s;
            int pos = 4;
            while (line.at(pos) != ',') {
                s += line.at(pos);
                pos++;
            }
            istringstream(s) >> x1;
            pos++;
            s.clear();
            while (line.at(pos) != ',') {
                s += line.at(pos);
                pos++;
            }
            istringstream(s) >> y1;
            pos++;
            s.clear();
            while (line.at(pos) != ',') {
                s += line.at(pos);
                pos++;
            }
            istringstream(s) >> x2;
            pos++;
            s.clear();
            while (line.at(pos) != ')') {
                s += line.at(pos);
                pos++;
            }
            pos++;
            istringstream(s) >> y2;
            windows[id] = make_pair(make_pair(min(x1, x2), min(y1, y2))
                    , make_pair(max(x1, x2), max(y1, y2)));
            depth[id] = topCounter--;
        } else {
            if (line.at(0) == 't') {
                depth[id] = topCounter--;
            } else if (line.at(0) == 'b') {
                depth[id] = bottomCounter++;
            } else if (line.at(0) == 'd') {
                windows.erase(id);
                depth.erase(id);
            } else if (line.at(0) == 's') {
                set<window> partitions;
                partitions.insert(windows[id]);
                for (map<char, window>::iterator it = windows.begin()
                        ; it != windows.end()
                        ; it++) {
                    char idOther = it->first;
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
                int totalArea = (windows[id].second.first - windows[id].first.first)
                    * (windows[id].second.second - windows[id].first.second);
                int areaVisible = 0;
                for (set<window>::iterator it = partitions.begin()
                        ; it != partitions.end()
                        ; it++) {
                    /*
                    cout << it->first.first << ' ' << it->first.second
                        << ' ' << it->second.first << ' ' << it->second.second << '\n';
                    */
                    areaVisible += (it->second.first - it->first.first)
                        * (it->second.second - it->first.second);
                }
                fout << fixed << setprecision(3) << (double) 100 * areaVisible
                    / totalArea << '\n';
            }
        }
    }
    return 0;
}
