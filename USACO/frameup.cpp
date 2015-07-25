#include <algorithm>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include <vector>
#include <set>

using namespace std;
typedef unsigned int u32;

void visit(list<u32> &lin, u32 node, vector<set<u32> > &g, vector<u32> &visited) {
	visited[node] = 1;
	if (!g[node].empty()) {
		for (set<u32>::iterator it = g[node].begin(); it != g[node].end(); it++) {
			if (visited[*it] == 0) {
				visit(lin, *it, g, visited);
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

list<u32> topologicalSort(vector<set<u32> > &g) {
	list<u32> lin;
	u32 n = g.size();
	//0 = not visited, 1 = currently visiting, 2 = visited
	vector<u32> visited(n);
	for (u32 i = 0; i < n; i++) {
		if (visited[i] == 0) {
			visit(lin, i, g, visited);
            //check to see if a cycle has been found by visit()
			if (lin.front() != i) {
				lin.clear();
                //return an empty list to indicate failure
				return lin;
			}
		}
	}
	return lin;
}

int main() {
    ifstream fin("frameup.in");
    ofstream fout("frameup.out");
}
