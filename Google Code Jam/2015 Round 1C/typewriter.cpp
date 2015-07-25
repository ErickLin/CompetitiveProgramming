#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
	u32 T;
	cin >> T;
	for (u32 t = 1; t <= T; t++) {
		u32 k, l, s;
		cin >> k >> l >> s;
		string keyboard, target;
		cin >> keyboard >> target;
		map<char, u32> freq;
		for (size_t i = 0; i < k; i++) {
			freq[keyboard.at(i)]++;
		}
		/*
		for (map<char, u32>::iterator i = freq.begin(); i != freq.end(); i++) {
			cout << i -> first << '-' << i -> second << ' ';
		}
		cout << '\n';
		*/
		//maps number of instances of target word to number of possible strings
		map<u32, u64> occurrences;
		u32 maxTimes = 0;
		stack<string> stk;
		stk.push("");
		while (!stk.empty()) {
			string top = stk.top();
			stk.pop();
			if (top.size() == s) {
				u32 count = 0;
				size_t pos = top.find(target, 0);
				while(pos != string::npos) {
					count++;
				    pos = top.find(target, pos + 1);
				}
				if (count > 0) {
					occurrences[count]++;
					if (count > maxTimes) {
						maxTimes = count;
					}
				}
			} else for (size_t i = 0; i < k; i++) {
				stk.push(top + keyboard.at(i));
			}
		}
		u64 numerator = 0, denominator = 1;
		for (map<u32, u64>::iterator i = occurrences.begin(); i != occurrences.end(); i++) {
			numerator += (i->first) * (i->second);
		}
		for (u32 i = 1; i <= s; i++) {
			denominator *= k;
		}
		double expected = ((double) numerator) / denominator;
		cout.precision(7);
		cout << "Case #" << t << ": " << (((double) maxTimes) - expected) << '\n';
	}
	return 0;
}