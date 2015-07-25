/*
ID: Jugglebrosjr2
LANG: C++
TASK: race3
*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <stack>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main(int argc, char** argv) {
    ifstream fin("race3.in");
    ofstream fout("race3.out");
    vector<set<u32> > g(51);
    //number of nodes
    u32 n = 0;
    int a;
    fin >> a;
    for (u32 p = 0; a != -1; p++) {
        while (a != -2) {
            g[p].insert(a);
            fin >> a;
        }
        fin >> a;
        n++;
    }
    set<u32> unavoidable;
    for (u32 removed = 1; removed < n - 1; removed++) {
        bool hasPath = false;
        stack<u32> stk;
        vector<bool> visited(n);
        stk.push(0);
        while (!stk.empty() && !hasPath) {
            u32 node = stk.top();
            stk.pop();
            if (node == n - 1) {
                hasPath = true;
            }
            else for (set<u32>::iterator i = g[node].begin(); i != g[node].end(); i++) {
                u32 neighbor = *i;
                if (neighbor != removed && !visited[neighbor]) {
                    stk.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        if (!hasPath) {
            unavoidable.insert(removed);
        }
    }
    fout << unavoidable.size();
    for (set<u32>::iterator i = unavoidable.begin(); i != unavoidable.end(); i++) {
        fout << ' ' << *i;
    }
    fout << '\n';
    set<u32> articulation;
    for (u32 removed = 1; removed < n - 1; removed++) {
        //connected components
        vector<set<u32> > components(n);
        //which component each node belongs in
        vector<int> setNum(n);
        fill(setNum.begin(), setNum.end(), -1);
        u32 componentNum = 0;
        for (u32 start = 0; start < n - 1; start++) {
            if (setNum[start] == -1) {
                stack<u32> stk;
                stk.push(start);
                setNum[start] = componentNum;
                components[componentNum].insert(start);
                while (!stk.empty()) {
                    u32 node = stk.top();
                    stk.pop();
                    for (set<u32>::iterator i = g[node].begin(); i != g[node].end(); i++) {
                        u32 neighbor = *i;
                        if (neighbor != removed) {
                            //if not yet visited, add to current component
                            //otherwise combine the two components
                            if (setNum[neighbor] == -1) {
                                stk.push(neighbor);
                                setNum[neighbor] = setNum[node];
                                components[setNum[node]].insert(neighbor);
                            } else if (setNum[node] < setNum[neighbor]) {
                                for (set<u32>::iterator i = components[setNum[neighbor]].begin(); i != components[setNum[neighbor]].end(); i++) {
                                    setNum[*i] = setNum[node];
                                    components[setNum[node]].insert(*i);
                                }
                                components[setNum[neighbor]].clear();
                            } else if (setNum[node] > setNum[neighbor]) {
                                setNum[node] = setNum[neighbor];
                                for (set<u32>::iterator i = components[setNum[node]].begin(); i != components[setNum[node]].end(); i++) {
                                    setNum[*i] = setNum[neighbor];
                                    components[setNum[neighbor]].insert(*i);
                                }
                                components[setNum[node]].clear();
                            }
                        }
                    }
                }
                componentNum++;
            }
        }
        if (setNum[0] != setNum[n - 1]) {
            articulation.insert(removed);
        }
    }
    fout << articulation.size();
    for (set<u32>::iterator i = articulation.begin(); i != articulation.end(); i++) {
        fout << ' ' << *i;
    }
    fout << '\n';
    return 0;
}