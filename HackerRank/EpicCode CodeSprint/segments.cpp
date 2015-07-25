#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

int cmp(pair<u32, u32> a, pair<u32, u32> b) {
	if (a.first == b.first) {
		return a.second < b.second;
	} else {
		return a.first < b.first;
	}
}

int main() {
	u32 n;
	cin >> n;
	vector<pair<u32, u32> > segs(n);
	for (u32 i = 0; i < n; i++) {
		u32 a, b;
		cin >> a >> b;
		segs[i] = make_pair(a, b);
	}
	sort(segs.begin(), segs.end(), &cmp);
	vector<u32> eqStart;
	eqStart.push_back(0);
	for (u32 i = 1; i < n; i++) {
		if (segs[i].first != segs[eqStart[eqStart.size() - 1]].first) {
			eqStart.push_back(i);
		}
	}
	eqStart.push_back(n);
	//this array, at every j, stores index k of the smallest value s.t.
	//there is an increasing subsequence of length j ending at k
	vector<u32> m(n + 1);
	u32 maxLen = 0;
	for (u32 i = 0; i < eqStart.size() - 1; i++) {
		map<u32, u32> newMs;
		for (u32 j = eqStart[i]; j < eqStart[i + 1]; j++) {
			u32 lo = 1, hi = maxLen;
			while (lo <= hi) {
				u32 mid = ceil(lo + ((hi - lo) >> 1));
				if (segs[m[mid]].second < segs[j].second) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			u32 newMaxLen = lo;
			if (newMs.find(newMaxLen) == newMs.end()
					|| newMs[newMaxLen] < eqStart[i]) {
				newMs[newMaxLen] = j;
			}
		}
		for (map<u32, u32>::iterator it = newMs.begin(); it != newMs.end(); it++) {
			m[it->first] = it->second;
			if (it->first > maxLen) {
				maxLen = it->first;
			}
		}
	}
	cout << maxLen << '\n';
	return 0;
}