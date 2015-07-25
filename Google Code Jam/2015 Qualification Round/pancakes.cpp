#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
	//ios_base::sync_with_stdio(false);
    ifstream fin("B-small-attempt0.in");
    ofstream fout("pancakes2.out");
    u32 T;
    fin >> T;
    for (u32 t = 1; t <= T; t++) {
	    u32 d;
	    fin >> d;
	    priority_queue<u32> pq;
	    for (u32 i = 0; i < d; i++) {
	    	u32 p;
	    	fin >> p;
	    	pq.push(p);
	    }
	    u32 min = 9999;
	    u32 numSpecial = 0;
	    while (!pq.empty()) {
	    	u32 elem = pq.top();
    		pq.pop();
	    	if (numSpecial + elem < min) {
	    		min = numSpecial + elem;
	    	}
    		pq.push(elem / 2);
    		if (elem % 2 == 0) {
    			pq.push(elem / 2);
    		} else {
    			pq.push(elem / 2 + 1);
    		}
	    	numSpecial++;
    		if (elem <= 3) {
    			break;
    		}
	    }
    	fout << "Case #" << t << ": " << min << '\n';
    }
    return 0;
}