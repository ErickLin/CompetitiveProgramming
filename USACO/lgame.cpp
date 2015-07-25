/*
ID: Jugglebrosjr2
LANG: C++
TASK: lgame
*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;

bool binary_search(string s, vector<string> &dict) {
	u32 lo = 0;
	u32 hi = dict.size() - 1;
	while (lo <= hi) {
		u32 mid = lo + (hi - lo) / 2;
		//cout << mid << ' ' << dict[mid] << '\n';
		if (s == dict[mid]) {
			return true;
		} else if (s > dict[mid]) {
			lo = mid + 1;
		} else {
			if (mid == 0) {
				return false;
			}
			hi = mid - 1;
		}
	}
	return false;
}

int main(int argc, char** argv) {
	ifstream din("lgame.dict");
	ifstream fin("lgame.in");
	ofstream fout("lgame.out");
	map<char, u32> pts;
	pts['q'] = 7;
	pts['w'] = 6;
	pts['e'] = 1;
	pts['r'] = 2;
	pts['t'] = 2;
	pts['y'] = 5;
	pts['u'] = 4;
	pts['i'] = 1;
	pts['o'] = 3;
	pts['p'] = 5;
	pts['a'] = 2;
	pts['s'] = 1;
	pts['d'] = 4;
	pts['f'] = 6;
	pts['g'] = 5;
	pts['h'] = 5;
	pts['j'] = 7;
	pts['k'] = 6;
	pts['l'] = 3;
	pts['z'] = 7;
	pts['x'] = 7;
	pts['c'] = 4;
	pts['v'] = 6;
	pts['b'] = 5;
	pts['n'] = 2;
	pts['m'] = 5;
	vector<string> dict;
	while (!din.eof()) {
		string s;
		din >> s;
		if (s != ".")
			dict.push_back(s);
	}
	string s;
	fin >> s;
	sort(s.begin(), s.end());
	u32 maxScore = 0;
	set<string> sols;
	do {
		//one word
		if (binary_search(s, dict)) {
			u32 score = 0;
			for (u32 i = 0; i < s.size(); i++) {
				score += pts[s.at(i)];
			}
			if (score > maxScore) {
				maxScore = score;
				sols.clear();
			}
			if (score == maxScore) {
				sols.insert(s);
			}
		}
		//two words
		for (size_t i = 1; i < s.size(); i++) {
			for (size_t j = i + 1; j <= s.size(); j++) {
				string a = s.substr(0, i);
				string b = s.substr(i, j - i);
				//cout << s << ' ' << a << ' ' << b << '\n';
				u32 score = 0;
				bool hasA = binary_search(a, dict);
				bool hasB = binary_search(b, dict);
				if (hasA) {
					for (u32 i = 0; i < a.size(); i++) {
						score += pts[a.at(i)];
					}
				}
				if (hasB) {
					for (u32 i = 0; i < b.size(); i++) {
						score += pts[b.at(i)];
					}
				}
				if (a == "prom" && b == "rag") {
					cout << score << '\n';
				}
				if (score > maxScore) {
					maxScore = score;
					sols.clear();
				}
				if (score == maxScore) {
					if (hasA && !hasB) {
						sols.insert(a);
					}
					if (hasB && !hasA) {
						sols.insert(b);
					}
					if (hasA && hasB) {
						if (a.compare(b) < 0) {
							sols.insert(a + " " + b);
						} else {
							sols.insert(b + " " + a);
						}
					}
				}
			}
		}
	} while (next_permutation(s.begin(), s.end()));
	fout << maxScore << '\n';
	for (set<string>::iterator it = sols.begin(); it != sols.end(); it++) {
		fout << *it << '\n';
	}
    return 0;
}