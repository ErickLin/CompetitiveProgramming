/*
ID: Jugglebrosjr2
LANG: C++
TASK: fence3
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> point;
typedef pair<int, point> segment;

int main() {
    ifstream fin("fence3.in");
    ofstream fout("fence3.out");
    int n;
    fin >> n;
    vector<segment> hSegs, vSegs;
    //vector<int> x, y;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            vSegs.push_back(make_pair(x1, make_pair(min(y1, y2), max(y1, y2))));
            //x.push_back(x1);
            //y.push_back(y1);
            //y.push_back(y2);
        } else {
            hSegs.push_back(make_pair(y1, make_pair(min(x1, x2), max(x1, x2))));
            //y.push_back(y1);
            //x.push_back(x1);
            //x.push_back(x2);
        }
    }
    /*
    //first idea: use endpoints of segments as reference points
    double ansX = 0, ansY = 0, ansDist = INT_MAX;
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < y.size(); j++) {
            int xSum = x[i];
            int xNum = 1;
            int ySum = y[i];
            int yNum = 1;
            for (int l = 0; l < hSegs.size(); l++) {
                if (l != i) {
                    if (hSegs[l].second.second < x[i]) {
                        xSum += hSegs[l].second.second;
                        xNum++;
                    } else if (hSegs[l].second.first > x[i]) {
                        xSum += hSegs[l].second.first;
                        xNum++;
                    }
                } 
                ySum += hSegs[l].first;
                yNum++;
            }
            for (int l = 0; l < vSegs.size(); l++) {
                if (l != j) {
                    if (vSegs[l].second.second < y[i]) {
                        ySum += vSegs[l].second.second;
                        yNum++;
                    } else if (vSegs[l].second.first > y[i]) {
                        ySum += vSegs[l].second.first;
                        yNum++;
                    }
                }
                xSum += vSegs[l].first;
                xNum++;
            }
            double xAvg = (double) xSum / xNum;
            double yAvg = (double) ySum / yNum;
            */
    /*
    //solution 1: brute force
    for (int xM = 0; xM <= 1000; xM++) {
        for (int yM = 0; yM <= 1000; yM++) {
            double x = (double) xM / 10;
            double y = (double) yM / 10;
            double dist = 0;
            for (int l = 0; l < hSegs.size(); l++) {
                double xDist = 0;
                if (hSegs[l].second.second < x) {
                    xDist = x- hSegs[l].second.second;
                } else if (hSegs[l].second.first > x) {
                    xDist = hSegs[l].second.first - x;
                }
                double yDist = hSegs[l].first - y;
                dist += sqrt(xDist * xDist + yDist * yDist);
            }
            for (int l = 0; l < vSegs.size(); l++) {
                double yDist = 0;
                if (vSegs[l].second.second < y) {
                    yDist = y- vSegs[l].second.second;
                } else if (vSegs[l].second.first > y) {
                    yDist = vSegs[l].second.first - y;
                }
                double xDist = vSegs[l].first - x;
                dist += sqrt(xDist * xDist + yDist * yDist);
            }
            if (dist < ansDist) {
                ansDist = dist;
                ansX = x;
                ansY = y;
            }
        }
    }
    */
    //solution 2: hill climb
    bool optReached = false;
    int currentXM = 0, currentYM = 0;
    double x = 0, y = 0, ansDist = 0;
    for (int l = 0; l < hSegs.size(); l++) {
        double xDist = 0;
        if (hSegs[l].second.second < x) {
            xDist = x- hSegs[l].second.second;
        } else if (hSegs[l].second.first > x) {
            xDist = hSegs[l].second.first - x;
        }
        double yDist = hSegs[l].first - y;
        ansDist += sqrt(xDist * xDist + yDist * yDist);
    }
    for (int l = 0; l < vSegs.size(); l++) {
        double yDist = 0;
        if (vSegs[l].second.second < y) {
            yDist = y- vSegs[l].second.second;
        } else if (vSegs[l].second.first > y) {
            yDist = vSegs[l].second.first - y;
        }
        double xDist = vSegs[l].first - x;
        ansDist += sqrt(xDist * xDist + yDist * yDist);
    }
    while (!optReached) {
        vector<point> ptsM(4);
        ptsM[0] = make_pair(currentXM - 1, currentYM);
        ptsM[1] = make_pair(currentXM + 1, currentYM);
        ptsM[2] = make_pair(currentXM, currentYM - 1);
        ptsM[3] = make_pair(currentXM, currentYM + 1);
        optReached = true;
        for (int i = 0; i < 4; i++) {
            if (ptsM[i].first >= 0 && ptsM[i].second >= 0) {
                x = (double) ptsM[i].first / 10;
                y = (double) ptsM[i].second / 10;
                double dist = 0;
                for (int l = 0; l < hSegs.size(); l++) {
                    double xDist = 0;
                    if (hSegs[l].second.second < x) {
                        xDist = x- hSegs[l].second.second;
                    } else if (hSegs[l].second.first > x) {
                        xDist = hSegs[l].second.first - x;
                    }
                    double yDist = hSegs[l].first - y;
                    dist += sqrt(xDist * xDist + yDist * yDist);
                }
                for (int l = 0; l < vSegs.size(); l++) {
                    double yDist = 0;
                    if (vSegs[l].second.second < y) {
                        yDist = y- vSegs[l].second.second;
                    } else if (vSegs[l].second.first > y) {
                        yDist = vSegs[l].second.first - y;
                    }
                    double xDist = vSegs[l].first - x;
                    dist += sqrt(xDist * xDist + yDist * yDist);
                }
                /*
                cout << x << ' ' << y << ' ';
                cout << ptsM[i].first << ' ' << ptsM[i].second << ' ';
                cout << dist << '\n';
                */
                if (dist <= ansDist) {
                    optReached = false;
                    ansDist = dist;
                    currentXM = ptsM[i].first;
                    currentYM = ptsM[i].second;
                }
            }
        }
    }
    fout << fixed << setprecision(1) << (double) currentXM / 10 << ' '
        << (double) currentYM / 10 << ' ' << ansDist << '\n';
    return 0;
}
