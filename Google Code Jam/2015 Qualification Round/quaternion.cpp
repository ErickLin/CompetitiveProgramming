#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
const int i = 2;
const int j = 3;
const int k = 4;

int product(int a, int b) {
	if (a == 1) {
		return b;
	} else if (a == -1) {
		return -b;
	} else if (b == 1) {
		return a;
	} else if (b == -1) {
		return -a;
	}
	int sign = 1;
	if (a < 0) {
		sign *= -1;
		a *= -1;
	}
	if (b < 0) {
		sign *= -1;
		b *= -1;
	}
	switch (a) {
	case i:
		switch (b) {
		case j:
			return sign * k;
		case k:
			return sign * -j;
		default:
			return sign * -1;
		}
	case j:
		switch (b) {
		case i:
			return sign * -k;
		case k:
			return sign * i;
		default:
			return sign * -1;
		}
	case k:
		switch (b) {
		case i:
			return sign * j;
		case j:
			return sign * -i;
		default:
			return sign * -1;
		}
	default:
		return 1;
	}
}

//b * ? = a
int quotient(int a, int b) {
	for (int c = -1; c >= -4; c--) {
		if (product(b, c) == a) {
			return c;
		}
	}
	for (int c = 1; c <= 4; c++) {
		if (product(b, c) == a) {
			return c;
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
    ifstream fin("C-small-attempt0.in");
    ofstream fout("quaternion.out");
    int T;
    fin >> T;
    for (int t = 1; t <= T; t++) {
    	int len, reps;
    	string s;
    	fin >> len >> reps >> s;
    	reps %= 12;
    	if (reps == 0) {
    		reps += 12;
    	}
    	vector<int> prefix(len);
    	prefix[0] = s.at(0) - 'i' + 2;
    	//cout << prefix[0] << ' ';
    	for (int pos = 1; pos < len; pos++) {
    		prefix[pos] = product(prefix[pos - 1], s.at(pos) - 'i' + 2);
    		//cout << prefix[pos] << ' ';
    	}
    	//cout << ' ';
    	vector<int> prefixRep(4);
    	prefixRep[0] = prefix[len - 1];
    	//cout << prefixRep[0] << ' ';
    	for (int rep = 1; rep < 4; rep++) {
    		prefixRep[rep] = product(prefixRep[rep - 1], prefix[len - 1]);
    		//cout << prefixRep[rep] << ' ';
    	}
    	//cout << '\n';
    	//cout << prefix[len - 1] << ' ' << prefix[0] << '\n';
    	//cout << quotient(prefix[len - 1], prefix[0]) << '\n';
    	bool attainable = false;
    	//Find number of repetitions before the first separator
    	for (int reps1 = 0; reps1 < min(reps, 4) && !attainable; reps1++) {
    		//Find the position right before the first separator
    		for (int pos1 = 0; pos1 < len; pos1++) {
    			int substr1;
    			if (reps1 == 0) {
    				substr1 = prefix[pos1];
    			} else {
    				substr1 = product(prefixRep[reps1 - 1], prefix[pos1]);
    			}
    			if (substr1 == i) {
    				//Find number of repetitions after the second separator
    				for (int reps3 = 0; reps3 < min(reps, 4) && reps1 + reps3 < reps; reps3++) {
			    		//Find the position right after the second separator
			    		for (int pos3 = len - 1; pos3 >= 0; pos3--) {
			    			//lower bounds pos1 sets on pos3
			    			if (reps1 + reps3 == reps - 1 && pos3 < pos1 + 2) {
			    				break;
			    			}
			    			int substr3;
			    			if (pos3 == 0) {
			    				substr3 = prefix[len - 1];
			    			} else {
			    				substr3 = quotient(prefix[len - 1], prefix[pos3 - 1]);
			    			}
			    			if (reps3 > 0) {
			    				substr3 = product(substr3, prefixRep[reps3 - 1]);
			    			}
			    			if (substr3 == k) {
			    				int substr2;
			    				if (reps1 + reps3 == reps - 1) {
			    					substr2 = quotient(prefix[pos3 - 1], prefix[pos1]);
			    				} else {
				    				if (pos1 == len - 1) {
				    					substr2 = 1;
				    				} else {
				    					substr2 = quotient(prefix[len - 1], prefix[pos1]);
				    				}
				    				int reps2;
				    				if (reps1 + reps3 < reps - 2) {
				    					reps2 = reps - reps1 - reps3 - 2;
				    					substr2 = product(substr2, prefixRep[reps2 - 1]);
				    				}
				    				if (pos3 > 0) {
				    					substr2 = product(substr2, prefix[pos3 - 1]);
				    				}
			    				}
			    				//cout << t << ' ' << substr1 << ' ' << substr2 << ' ' << substr3 << '\n';
			    				if (substr2 == j) {
			    					attainable = true;
			    				}
			    			}
			    		}
    				}
    			}
    		}
    	}
		if (attainable) {
			fout << "Case #" << t << ": YES\n";
		} else  {
			fout << "Case #" << t << ": NO\n";
		}
    }
    return 0;
}