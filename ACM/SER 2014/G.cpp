#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int hammingDist(string a, string b) {
    int dist = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a.at(i) != b.at(i)) {
            dist++;
        }
    }
    return dist;
}

string makeNewWord(string a, string b) {
    bool usedA = false, usedB = false;
    string c = "";
    for (int i = 0; i < a.size(); i++) {
        if (a.at(i) == b.at(i)) {
            c += a.at(i);
        } else if (!usedA && !usedB) {
            c += min(a.at(i), b.at(i));
            if (a.at(i) < b.at(i)) {
                usedA = true;
            } else {
                usedB = true;
            }
        } else if (usedA) {
            c += b.at(i);
            usedB = true;
        } else if (usedB) {
            c += a.at(i);
            usedA = true;
        }
    }
    return c;
}

struct state {
    int node;
    bool usedWord;
    string newWord;
};

int main() {
    int n;
    cin >> n;
    vs words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
    vvb hasEdge(n, vb(n)), reqNewWord(n, vb(n));
    vvs interWords(n, vs(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int dist = hammingDist(words[i], words[j]);
                if (dist <= 2) {
                    hasEdge[i][j] = true;
                    hasEdge[j][i] = true;
                }
                if (dist == 2) {
                    reqNewWord[i][j] = true;
                    reqNewWord[j][i] = true;
                    interWords[i][j] = makeNewWord(words[i], words[j]);
                    interWords[j][i] = interWords[i][j];
                }
            }
        }
    }
    string bestWord = "0";
    vi dists(n);
    fill(dists.begin(), dists.end(), -1);
    vi distsNewWord(n);
    fill(distsNewWord.begin(), distsNewWord.end(), -1);
    vs newWords(n);
    fill(newWords.begin(), newWords.end(), "0");
    dists[0] = 0;
    distsNewWord[0] = 0;
    queue<state> q;

    state start;
    start.node = 0;
    start.usedWord = false;
    start.newWord = "0";
    q.push(start);
    while (!q.empty()) {
        state curr = q.front();
        q.pop();
        if (curr.usedWord) {
            for (int i = 1; i < n; i++) {
                if (hasEdge[curr.node][i] && !reqNewWord[curr.node][i]
                        && (distsNewWord[i] == -1 || distsNewWord[i] > distsNewWord[curr.node] + 1
                        || (distsNewWord[i] == distsNewWord[curr.node] + 1 && newWords[i] > curr.newWord))) {
                    distsNewWord[i] = distsNewWord[curr.node] + 1;
                    newWords[i] = curr.newWord;

                    state next;
                    next.node = i;
                    next.usedWord = true;
                    next.newWord = curr.newWord;
                    q.push(next);
                }
            }
        } else {
            for (int i = 1; i < n; i++) {
                if (hasEdge[curr.node][i] && !reqNewWord[curr.node][i]
                        && (dists[i] == -1 || dists[i] > dists[curr.node] + 1)) {
                    dists[i] = dists[curr.node] + 1;

                    state next;
                    next.node = i;
                    next.usedWord = false;
                    next.newWord = "0";
                    q.push(next);
                }
            }
            for (int i = 1; i < n; i++) {
                if (hasEdge[curr.node][i] && reqNewWord[curr.node][i]
                        && (distsNewWord[i] == -1 || distsNewWord[i] > dists[curr.node] + 2
                        || (distsNewWord[i] == dists[curr.node] + 2 && newWords[i] != "0"
                        && newWords[i] > interWords[curr.node][i]))) {
                    distsNewWord[i] = dists[curr.node] + 2;
                    newWords[i] = interWords[curr.node][i];

                    state next;
                    next.node = i;
                    next.usedWord = true;
                    next.newWord = interWords[curr.node][i];
                    q.push(next);
                }
            }
        }
    }
    if (dists[1] == -1 || (distsNewWord[1] != -1 && distsNewWord[1] < dists[1])) {
        cout << newWords[1] << '\n' << distsNewWord[1] << '\n';
    } else {
        cout << "0\n" << dists[1] << '\n';
    }
    return 0;
}
