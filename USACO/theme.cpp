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
    for (int i = 0; i < n; i++) {
        fin >> notes[i];
    }
    int maxLen = 0;
    for (int i = 1; i < n; i++) {
        int len = 1;
        for (int j = 0; j < n - i; j++) {
            if ((notes[j + 1] - notes[j]) == (notes[i + j + 2] - notes[i + j + 1])) {
                if (len <= i) {
                    len++;
                }
                if (len > maxLen) {
                    maxLen = len;
                }
            } else {
                len = 1;
            }
        }
    }
    fout << (maxLen < 5 ? 0 : maxLen) << '\n';
    return 0;
}
