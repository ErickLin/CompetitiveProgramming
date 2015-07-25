#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
	ios_base::sync_with_stdio(false);
    ifstream fin("A-large.in");
    ofstream fout("ovation2.out");
    u32 t;
    fin >> t;
    for (u32 i = 1; i <= t; i++) {
    	u32 n;
    	fin >> n;
    	string s;
    	fin >> s;
    	u32 sum = 0, add = 0;
    	for (u32 j = 0; j < s.size(); j++) {
    		if (sum < j) {
    			add += j - sum;
    			sum = j;
    		}
    		sum += s.at(j) - '0';
    	}
    	fout << "Case #" << i << ": " << add << '\n';
    }
    return 0;
}