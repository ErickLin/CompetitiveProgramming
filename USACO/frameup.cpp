/*
ID: Jugglebrosjr2
LANG: C++
TASK: frameup
*/
#include <algorithm>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <string>

using namespace std;

/*
void dfs(list<char> &lin, char node, map<char, set<char> > &g, map<char, int> &visited) {
	visited[node] = 1;
	if (!g[node].empty()) {
		for (set<char>::iterator it = g[node].begin(); it != g[node].end(); it++) {
			if (visited.find(*it) == visited.end()) {
				dfs(lin, *it, g, visited);
				if (lin.front() != *it) {
					lin.clear();
					return;
				}
			} else if (visited[*it] == 1) {
				//found cycle
				return;
			}
		}
	}
	visited[node] = 2;
	lin.push_front(node);
}

list<char> topologicalSort(map<char, set<char> > &g) {
	list<char> lin;
	//1 = currently visiting, 2 = visited
	map<char, int> visited;
    for (map<char, set<char> >::iterator it = g.begin(); it != g.end(); it++) {
		if (visited.find(it->first) == visited.end()) {
			dfs(lin, it->first, g, visited);
            //check to see if a cycle has been found by dfs()
			if (lin.front() != it->first) {
				lin.clear();
                //return an empty list to indicate failure
				return lin;
			}
		}
	}
	return lin;
}
*/

struct props {
    int left;
    int top;
    int right;
    int bottom;
};

void gen(string accum, map<char, set<char> > &g, vector<char> &letters
        , vector<string> &ans) {
    if (accum.length() == letters.size()) {
        ans.push_back(accum);
    } else {
        char letter = letters[accum.size()];
        //bounds indicate the minimum position before which the current letter
        //can be placed
        int lowerBound = 0;
        int upperBound = accum.length();
        for (int i = 0; i < accum.length(); i++) {
            if (g[accum.at(i)].find(letter) != g[accum.at(i)].end()) {
                lowerBound = i + 1;
            }
            if (g[letter].find(accum.at(i)) != g[letter].end()) {
                upperBound = min(upperBound, i);
            }
        }
        for (int i = lowerBound; i <= upperBound; i++) {
            if (i == 0) {
                gen(letter + accum, g, letters, ans);
            } else if (i == accum.length()) {
                gen(accum + letter, g, letters, ans);
            } else {
                gen(accum.substr(0, i) + letter + accum.substr(i, accum.length() - i)
                        , g, letters, ans);
            }
        }
    }
}

int main() {
    ifstream fin("frameup.in");
    ofstream fout("frameup.out");
    map<char, struct props> frames;
    int h, w;
    fin >> h >> w;
    vector<vector<char> > wall(h, vector<char>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char letter;
            fin >> letter;
            wall[i][j] = letter;
            if (letter != '.') {
                if (frames.find(letter) == frames.end()) {
                    frames[letter].left = j;
                    frames[letter].top = i;
                    frames[letter].right = j;
                    frames[letter].bottom = i;
                } else {
                    if (j < frames[letter].left) {
                        frames[letter].left = j;
                    }
                    if (i < frames[letter].top) {
                        frames[letter].top = i;
                    }
                    if (j > frames[letter].right) {
                        frames[letter].right = j;
                    }
                    if (i > frames[letter].bottom) {
                        frames[letter].bottom = i;
                    }
                }
            }
        }
    }
    map<char, set<char> > g;
    vector<char> letters;
    for (map<char, struct props>::iterator it = frames.begin(); it != frames.end(); it++) {
        //initialize the set
        g[it->first].insert('.');
        g[it->first].erase('.');
        for (int i = it->second.top; i <= it->second.bottom; i++) {
            int a = it->second.left;
            int b = it->second.right;
            if (it->first != '.' && wall[i][a] != '.' && wall[i][a] != it->first) {
                g[it->first].insert(wall[i][a]);
            }
            if (it->first != '.' && wall[i][b] != '.' && wall[i][b] != it->first) {
                g[it->first].insert(wall[i][b]);
            }
        }
        for (int j = it->second.left; j <= it->second.right; j++) {
            int a = it->second.top;
            int b = it->second.bottom;
            if (it->first != '.' && wall[a][j] != '.' && wall[a][j] != it->first) {
                g[it->first].insert(wall[a][j]);
            }
            if (it->first != '.' && wall[b][j] != '.' && wall[b][j] != it->first) {
                g[it->first].insert(wall[b][j]);
            }
        }
        letters.push_back(it->first);
    }
    /*
    for (map<char, set<char> >::iterator it = g.begin(); it != g.end(); it++) {
        cout << it->first << ": ";
        for (set<char>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << *it2 << ' ';
        }
        cout << '\n';
    }
    */
    /*
    list<char> ordered = topologicalSort(g);
    for (list<char>::iterator it = ordered.begin(); it != ordered.end(); it++) {
        fout << *it;
    }
    fout << '\n';
    */
    vector<string> ans;
    string s;
    s += letters[0];
    gen(s, g, letters, ans);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i] << '\n';
    }
    return 0;
}
