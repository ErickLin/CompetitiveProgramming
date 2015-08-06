/*
ID: Jugglebrosjr2
LANG: C++
TASK: picture
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct line {
    int pos, start, end, rectNum;
    bool isStart;
};

bool operator<(const line &a, const line &b) {
    if (a.pos == b.pos) {
        if (a.isStart == b.isStart) {
            if (a.start == b.start) {
                if (a.end == b.end) {
                    return a.rectNum < b.rectNum;
                }
                return a.end < b.end;
            }
            return a.start < b.start;
        }
        //starting should come first in order
        return a.isStart > b.isStart;
    }
    return a.pos < b.pos;
}

struct rect {
    struct line hLine1, hLine2, vLine1, vLine2;
};

int main() {
    ifstream fin("picture.in");
    ofstream fout("picture.out");
    int n;
    fin >> n;
    vector<struct line> vLines;
    vector<struct line> hLines;
    vector<struct rect> rects(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        /*
        int x1Top = x1, x2Top = x2, x1Bot = x1, x2Bot = x2, y1Left = y1
            , y2Left = y2, y1Right = y1, y2Right = y2;
        set<line> add;
        set<line> remove;
        for (set<line>::iterator it = xLines.begin(); it != xLines.end(); it++) {
            
        }
        for (set<line>::iterator it = add.begin(); it != add.end(); it++) {
            xLines.insert(*it);
        }
        for (set<line>::iterator it = remove.begin(); it != remove.end(); it++) {
            xLines.erase(*it);
        }
        xLines.insert(make_pair(y1, make_pair(x1, x2)));
        xLines.insert(make_pair(y2, make_pair(x1, x2)));
        yLines.insert(make_pair(x1, make_pair(y1, y2)));
        yLines.insert(make_pair(x2, make_pair(y1, y2)));
        */
        struct line hLine1;
        hLine1.pos = y1;
        hLine1.start = x1;
        hLine1.end = x2;
        hLine1.rectNum = i;
        hLine1.isStart = true;
        struct line hLine2;
        hLine2.pos = y2;
        hLine2.start = x1;
        hLine2.end = x2;
        hLine2.rectNum = i;
        hLine2.isStart = false;
        struct line vLine1;
        vLine1.pos = x1;
        vLine1.start = y1;
        vLine1.end = y2;
        vLine1.rectNum = i;
        vLine1.isStart = true;
        struct line vLine2;
        vLine2.pos = x2;
        vLine2.start = y1;
        vLine2.end = y2;
        vLine2.rectNum = i;
        vLine2.isStart = false;
        struct rect current;
        current.hLine1 = hLine1;
        current.hLine2 = hLine2;
        current.vLine1 = vLine1;
        current.vLine2 = vLine2;

        hLines.push_back(hLine1);
        hLines.push_back(hLine2);
        vLines.push_back(vLine1);
        vLines.push_back(vLine2);
        rects[i] = current;
    }
    sort(hLines.begin(), hLines.end());
    sort(vLines.begin(), vLines.end());
    int perim = 0;
    //stores vertical lines that are currently intersecting the sweep-line
    set<struct line> at;
    //begin scan-line process to find perimeter of horizontal lines
    for (int i = 0; i < hLines.size(); i++) {
        //starting event: add vertical lines belonging to same rectangle
        if (hLines[i].isStart) {
            at.insert(rects[hLines[i].rectNum].vLine1);
            at.insert(rects[hLines[i].rectNum].vLine2);
        }
        //keep track of current number of rectangles intersecting current vertical line
        //in inner loop
        int numRects = 0;
        //cout << "Next line: " << hLines[i].pos << ' ' << (hLines[i].isStart ? "start" : "end") << '\n';
        //whether we have intersected current rectangle (and should start counting
        //perimeter length)
        bool started = false;
        //starting x-position (if we are intersecting current rectangle only)
        int start = -1;
        //begin inner loop (scan-line process) to calculate contribution of current
        //horizontal line event to perimeter
        for (set<struct line>::iterator it = at.begin(); it != at.end(); it++) {
            if (it->isStart) {
                numRects++;
                if (it->rectNum == hLines[i].rectNum) {
                    started = true;
                }
            } else {
                numRects--;
            }
            if (started) {
                if (numRects == 1) {
                    start = it->pos;
                } else {
                    if (start != -1) {
                        perim += it->pos - start;
                        start = -1;
                    }
                }
            }
            if (!it->isStart && it->rectNum == hLines[i].rectNum) {
                started = false;
                break;
            }
        }
        //ending event: remove vertical lines belonging to same rectangle
        if (!hLines[i].isStart) {
            at.erase(rects[hLines[i].rectNum].vLine1);
            at.erase(rects[hLines[i].rectNum].vLine2);
        }
    }
    //now stores horizontal lines that are currently intersecting the sweep-line
    at.clear();
    //same as above, but with vertical lines this time
    for (int i = 0; i < vLines.size(); i++) {
        if (vLines[i].isStart) {
            at.insert(rects[vLines[i].rectNum].hLine1);
            at.insert(rects[vLines[i].rectNum].hLine2);
        }
        int numRects = 0;
        //cout << "Next line: " << vLines[i].pos << ' ' << (vLines[i].isStart ? "start" : "end") << '\n';
        bool started = false;
        int start = -1;
        for (set<struct line>::iterator it = at.begin(); it != at.end(); it++) {
            //cout << it->pos << ' ' << (it->isStart ? "start" : "end") << '\n';
            if (it->isStart) {
                numRects++;
                if (it->rectNum == vLines[i].rectNum) {
                    started = true;
                }
            } else {
                numRects--;
            }
            if (started) {
                if (numRects == 1) {
                    start = it->pos;
                } else {
                    if (start != -1) {
                        perim += it->pos - start;
                        start = -1;
                    }
                }
            }
            if (!it->isStart && it->rectNum == vLines[i].rectNum) {
                started = false;
                break;
            }
        }
        //cout << perim << '\n';
        if (!vLines[i].isStart) {
            at.erase(rects[vLines[i].rectNum].hLine1);
            at.erase(rects[vLines[i].rectNum].hLine2);
        }
    }
    fout << perim << '\n';
    return 0;
}
