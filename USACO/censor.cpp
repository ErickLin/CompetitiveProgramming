/*
ID: Jugglebrosjr2
LANG: C++
TASK: censor
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> buildTable(string w) {
    vector<int> t(w.size());
    t[0] = -1;
    t[1] = 0;
    int pos = 2;
    int candidatePos = 0;
    while (pos < w.size()) {
        if (w.at(pos - 1) == w.at(candidatePos)) {
            candidatePos++;
            t[pos] = candidatePos;
            pos++;
        } else if (candidatePos > 0) {
            candidatePos = t[candidatePos];
        } else {
            t[pos] = 0;
            pos++;
        }
    }
    return t;
}

int getMatchingPos(string s, string w) {
    int m = 0;
    int i = 0;
    vector<int> t = buildTable(w);
    while (m + i < s.size()) {
        if (w.at(i) == s.at(m + i)) {
            if (i == w.size() - 1) {
                return m;
            }
            i++;
        } else {
            if (t[i] > -1) {
                m += i - t[i];
                i = t[i];
            } else {
                i = 0;
                m++;
            }
        }
    }
    return s.size();
}

int main(int argc, char** argv) {
    ifstream fin("censor.in");
    ofstream fout("censor.out");
    string s;
    fin >> s;
    /*
    vector<char> s(sTemp.size());
    for (int i = 0; i < sTemp.size(); i++) {
    	s[i] = sTemp.at(i);
    }
    */
    int n;
    fin >> n;
    vector<string> t(n);
    for (int i = 0; i < n; i++) {
    	fin >> t[i];
	    //fout << t[i] << '\n';
	    int pos = getMatchingPos(s, t[i]);
    	//fout << pos << '\n';
    	s.erase(pos, t[i].size());
    }
    for (int j = 0; j < n; j++) {
	    for (int i = 0; i < n; i++) {
	    	s.erase(getMatchingPos(s, t[i]), t[i].size());
	    }
	}
    fout << s << '\n';
    return 0;
}