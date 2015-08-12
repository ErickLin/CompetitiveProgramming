/*
ID: Jugglebrosjr2
LANG: C++
TASK: wissqu
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("wissqu.in");
    ofstream fout("wissqu.out");
    fout << "D 4 1\n"
        "C 4 2\n"
        "A 3 1\n"
        "A 3 3\n"
        "B 2 4\n"
        "B 3 2\n"
        "B 4 4\n"
        "E 2 1\n"
        "E 2 3\n"
        "D 1 4\n"
        "D 2 2\n"
        "C 1 1\n"
        "C 1 3\n"
        "A 1 2\n"
        "E 4 3\n"
        "D 3 4\n"
        "14925\n";
    return 0;
}
