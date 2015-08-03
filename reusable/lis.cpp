#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

//returns the length of the longest increasing subsequence of a
int lis(vector<int> &a) {
	int n = a.size();
	//this array, at every j, stores index k of the smallest value s.t.
	//there is an increasing subsequence of length j ending at k
	vector<int> m(n + 1);
	int maxLen = 0;
	for (int i = 0; i < n; i++) {
		int lo = 1, hi = maxLen;
		while (lo <= hi) {
			int mid = ceil(lo + ((hi - lo) >> 1));
			if (a[m[mid]] < a[i]) {
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}
		m[lo] = i;
		maxLen = max(maxLen, lo);
	}
	return maxLen;
}