/*
ID: Jugglebrosjr2
LANG: C++
TASK: starry
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;

int main() {
    ifstream fin("starry.in");
    ofstream fout("starry.out");
    int w, h;
    fin >> w >> h;
    vector<vector<char> > sky(h, vector<char>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fin >> sky[i][j];
        }
    }
    //stores all the stars' positions relative from the top-left
    //star of the cluster
    map<set<pair<int, int> >, char> clusters;
    //helps with dfs
    set<pair<int, int> > neighbors;
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            if (a != 0 || b != 0) {
                neighbors.insert(make_pair(a, b));
            }
        }
    }
    char currentLetter = 'a';
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (sky[i][j] == '1') {
                stack<pair<int, int> > s;
                set<pair<int, int> > visited;
                int rOffset = 0, cOffset = 0;
                s.push(make_pair(i, j));
                visited.insert(make_pair(i, j));
                while (!s.empty()) {
                    pair<int, int> star = s.top();
                    s.pop();
                    for (set<pair<int, int> >::iterator it = neighbors.begin();
                            it != neighbors.end(); it++) {
                        int r = star.first + it->first;
                        int c = star.second + it->second;
                        if (r >= 0 && r < h && c >= 0 && c < w
                                && sky[r][c] == '1'
                                && visited.find(make_pair(
                                    r, c)) == visited.end()
                                ) {
                            if (r - i < rOffset) {
                                rOffset = r - i;
                            }
                            if (c - j < cOffset) {
                                cOffset = c - j;
                            }
                            s.push(make_pair(r, c));
                            visited.insert(make_pair(r, c));
                        }
                    }
                }
                set<pair<int, int> > cluster;
                //left and top will both be re-aligned to 0
                int right = 0, bottom = 0;
                for (set<pair<int, int> >::iterator it = visited.begin();
                        it != visited.end(); it++) {
                    cluster.insert(make_pair(it->first - i - rOffset
                            , it->second - j - cOffset));
                    if (it->first - i - rOffset > bottom) {
                        bottom = it->first - i - rOffset;
                    }
                    if (it->second - j - cOffset > right) {
                        right = it->second - j - cOffset;
                    }
                }
                int letter;
                if (clusters.find(cluster) == clusters.end()) {
                    letter = currentLetter++;
                    set<pair<int, int> > cluster2;
                    set<pair<int, int> > cluster3;
                    set<pair<int, int> > cluster4;
                    set<pair<int, int> > cluster5;
                    set<pair<int, int> > cluster6;
                    set<pair<int, int> > cluster7;
                    set<pair<int, int> > cluster8;
                    for (set<pair<int, int> >::iterator it = cluster.begin();
                            it != cluster.end(); it++) {
                        cluster2.insert(make_pair(bottom - it->first
                                    , it->second));
                        cluster3.insert(make_pair(it->first
                                    , right - it->second));
                        cluster4.insert(make_pair(bottom - it->first
                                    , right - it->second));
                        cluster5.insert(make_pair(it->second
                                    , it->first));
                        cluster6.insert(make_pair(right - it->second
                                    , it->first));
                        cluster7.insert(make_pair(it->second
                                    , bottom - it->first));
                        cluster8.insert(make_pair(right - it->second
                                    , bottom - it->first));
                    }
                    clusters[cluster] = letter;
                    clusters[cluster2] = letter;
                    clusters[cluster3] = letter;
                    clusters[cluster4] = letter;
                    clusters[cluster5] = letter;
                    clusters[cluster6] = letter;
                    clusters[cluster7] = letter;
                    clusters[cluster8] = letter;
                } else {
                    letter = clusters[cluster];
                }
                for (set<pair<int, int> >::iterator it = visited.begin();
                        it != visited.end(); it++) {
                    sky[it->first][it->second] = letter;
                }
            }
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            //cout << (sky[i][j] == '0' ? ' ' : sky[i][j]);
            fout << sky[i][j];
        }
        //cout << '\n';
        fout << '\n';
    }
}
