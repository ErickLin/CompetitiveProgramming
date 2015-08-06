/*
ID: Jugglebrosjr2
LANG: C++
TASK: hidden
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");
    int n;
    fin >> n;
    vector<char> s(n);
    list<int> cand;
    for (int i = 0; i < n; i++) {
        fin >> s[i];
        cand.push_back(i);
    }
    for (int pos = 0; pos < (n << 1); pos++) {
        //cout << "Offset: " << pos << '\n';
        char least = 'z';
        for (list<int>::iterator it = cand.begin(); it != cand.end(); it++) {
            char c = s[(*it + pos) % n];
            //cout << "Candidate: " << *it << ' ' << c << '\n';
            least = min(least, c);
        }
        //cout << "Least: " << least << '\n';
        int prevElem = -1;
        int maxStreak = 1;
        list<int> maxStreakStart;
        int streak = 0;
        int streakStart = -1;
        bool changed = false;
        int k = cand.size();
        for (int i = 0; i < (k << 1); i++) {
            int elem = cand.front();
            cand.pop_front();
            char c = s[(elem + pos) % n];
            //cout << "Test: " << elem << ' ' << c << '\n';
            /*
            if (c == least) {
                //still minimal so put back in candidate list
                cand.push_back(elem);
            } else {
                cout << "Removed: " << elem << ' ' << c << '\n';
                changed = true;
            }
            */
            cand.push_back(elem);
            if (c != least || elem != (prevElem + 1) % n) {
                streak = 0;
            }
            if (c == least) {
                if (streak == 0) {
                    streakStart = elem;
                    if (i >= k) {
                        break;
                    }
                }
                if (streak == 0 || elem == (prevElem + 1) % n) {
                    streak++;
                }
                if (streak == maxStreak) {
                    maxStreakStart.push_back(streakStart);
                    //cout << "Streak start: " << streakStart << '\n';
                } else if (streak > maxStreak) {
                    maxStreak = streak;
                    maxStreakStart.clear();
                    maxStreakStart.push_back(streakStart);
                    //cout << "New streak: " << maxStreak << '\n';
                    //cout << "Streak start: " << streakStart << '\n';
                }
            }
            prevElem = elem;
        }
        if (cand == maxStreakStart) {
            break;
        }
        cand = maxStreakStart;
        //cout << "Number of candidates remaining: " << cand.size() << '\n';
        //cout << "Max streak: " << maxStreak << "\n\n";
        pos += maxStreak - 1;
        //If nothing is removed from the candidate list then all the remaining
        //elements are equally lexicographically minimal
        /*
        if (!changed) {
            break;
        }
        */
    }
    fout << cand.front() << '\n';
    return 0;
}
