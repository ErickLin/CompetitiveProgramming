#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef int u32;

int main() {
	u32 n, q;
	cin >> n >> q;
	vector<u32> arr(n * 2);
	fill(arr.begin(), arr.end(), 100000);
	u32 blkSize = (int) sqrt(n);
	vector<u32> blkMins((int) sqrt(n) + 1);
	fill(blkMins.begin(), blkMins.end(), INT_MAX);
	vector<u32> blkMinLocs((int) sqrt(n) + 1);
	fill(blkMinLocs.begin(), blkMinLocs.end(), INT_MAX);
	vector<bool> blkHas0((int) sqrt(n) + 1);
	//Length of longest chain of 1's in the block
	vector<u32> blkMaxLen1s((int) sqrt(n) + 1);
	//End position of longest chain of 1's
	vector<u32> blkMaxEnds1s((int) sqrt(n) + 1);
	fill(blkMinLocs.begin(), blkMinLocs.end(), INT_MAX);
	//Length of chain of 1's touching the left edge of the block
	vector<u32> blkLeftLens1s((int) sqrt(n) + 1);
	//Length of chain of 1's touching the right edge of the block
	vector<u32> blkRightLens1s((int) sqrt(n) + 1);
	//Calculate min
	for (u32 k = 0; k < n; k++) {
		cin >> arr[k];
		if (arr[k] < blkMins[k / blkSize]) {
			blkMins[k / blkSize] = arr[k];
			blkMinLocs[k / blkSize] = k;
			if (arr[k] == 0) {
				blkHas0[k / blkSize] = true;
			}
		}
	}
	//Calculate lengths of chains of 1 in each block
	for (u32 blk = 0; blk <= (int) sqrt(n); blk++) {
		u32 len1s = 0;
		for (u32 k = 0; k < blkSize; k++) {
			u32 pos = blk * blkSize + k;
			if (arr[pos] == 1) {
				len1s++;
				if (len1s > blkMaxLen1s[blk]) {
					blkMaxLen1s[blk] = len1s;
					blkMaxEnds1s[blk] = pos;
				}
			} else {
				len1s = 0;
			}
		}
		for (u32 k = 0; k < blkSize && arr[blk * blkSize + k] == 1 && (blk * blkSize + k - 1 < 0
					|| arr[blk * blkSize + k - 1] == 1); k++) {
			blkLeftLens1s[blk]++;
		}
		for (u32 k = blkSize - 1; k >= 0 && arr[blk * blkSize + k] == 1 && (blk * blkSize + k + 1 >= n
					|| arr[blk * blkSize + k + 1] == 1); k--) {
			blkRightLens1s[blk]++;
		}
	}
	//start going through queries
	for (u32 i = 0; i < q; i++) {
		u32 queryType;
		cin >> queryType;
		if (queryType == 1) {
			u32 i, j;
			cin >> i >> j;
			i--;
			j--;
			u32 minElem = INT_MAX, minLoc = INT_MAX, maxLen1s = 0, maxEnd1s = INT_MAX, leftOver1s = 0;
			bool has0 = false;
			//share the same block
			if (i / blkSize == (j - 1) / blkSize) {
				u32 len1s = 0;
				for (u32 k = i; k <= j; k++) {
					if (arr[k] < minElem) {
						minElem = arr[k];
						minLoc = k;
						if (arr[k] == 0) {
							has0 = true;
						}
					}
					if (arr[k] == 1) {
						len1s++;
						if (len1s > maxLen1s) {
							maxLen1s = len1s;
							maxEnd1s = k;
						}
					} else {
						len1s = 0;
					}
				}
			} else {
				u32 len1s = 0;
				//start in the middle of the first block
				for (u32 k = i; k % blkSize != 0; k++) {
					if (arr[k] < minElem) {
						minElem = arr[k];
						minLoc = k;
						if (arr[k] == 0) {
							has0 = true;
						}
					}
					if (arr[k] == 1) {
						len1s++;
						if (len1s > maxLen1s) {
							maxLen1s = len1s;
							maxEnd1s = k;
						}
						if ((k + 1) % blkSize == 0) {
							leftOver1s = len1s;
						}
					} else {
						len1s = 0;
					}
				}
				//check all blocks
				for (u32 blk = ((i % blkSize == 0) ? (i / blkSize) : (i / blkSize + 1));
						 blk <= ((j % blkSize == blkSize - 1) ? (j / blkSize) : (j / blkSize - 1));
						 blk++) {
					if (blkMins[blk] < minElem) {
						minElem = blkMins[blk];
						minLoc = blkMinLocs[blk];
						if (blkHas0[blk]) {
							has0 = true;
						}
					}
					if (leftOver1s + blkLeftLens1s[blk] > maxLen1s) {
						maxLen1s = leftOver1s + blkLeftLens1s[blk];
						maxEnd1s = blk * blkSize + blkLeftLens1s[blk] - 1;
					}
					if (blkMaxLen1s[blk] > maxLen1s) {
						maxLen1s = blkMaxLen1s[blk];
						maxEnd1s = blkMaxEnds1s[blk];
					}
					if (blkRightLens1s[blk] < blkSize) {
						leftOver1s = 0;
					}
					leftOver1s += blkRightLens1s[blk];
					//cout << "Blk " << blk << ' ' << blkLeftLens1s[blk] << ' ' << blkRightLens1s[blk] << '\n';
				}
				//end in the middle of the last block
				len1s = leftOver1s;
				for (u32 k = (j + 1) / blkSize * blkSize; k <= j; k++) {
					if (arr[k] < minElem) {
						minElem = arr[k];
						minLoc = k;
						if (arr[k] == 0) {
							has0 = true;
						}
					}
					if (arr[k] == 1) {
						len1s++;
						if (len1s > maxLen1s) {
							maxLen1s = len1s;
							maxEnd1s = k;
						}
						if ((k + 1) % blkSize == 0) {
							leftOver1s = len1s;
						}
					} else {
						len1s = 0;
					}
				}
			}
			if (has0) {
				cout << minElem << ' ' << (i + 1) << ' ' << (j + 1) << '\n';
			} else if (minElem == 1) {
				cout << minElem << ' ' << (maxEnd1s - maxLen1s + 2) << ' ' << (maxEnd1s + 1) << '\n';
			} else {
				cout << minElem << ' ' << (minLoc + 1) << ' ' << (minLoc + 1) << '\n';
			}
		} else {
			u32 i, v;
			cin >> i >> v;
			i--;
			arr[i] = v;
			u32 blk = i / blkSize;
			blkMins[blk] = INT_MAX;
			blkMinLocs[blk] = INT_MAX;
			blkHas0[blk] = false;
			blkMaxLen1s[blk] = 0;
			blkMaxEnds1s[blk] = INT_MAX;
			blkLeftLens1s[blk] = 0;
			blkRightLens1s[blk] = 0;
			//Re-calculate min
			for (u32 k = 0; k < blkSize; k++) {
				u32 i = blk * blkSize + k;
				if (arr[i] < blkMins[blk]) {
					blkMins[blk] = arr[i];
					blkMinLocs[blk] = i;
					if (arr[i] == 0) {
						blkHas0[blk] = true;
					}
				}
			}
			//Re-calculate lengths of chains of 1
			u32 len1s = 0;
			for (u32 k = 0; k < blkSize; k++) {
				u32 pos = blk * blkSize + k;
				if (arr[pos] == 1) {
					len1s++;
					if (len1s > blkMaxLen1s[blk]) {
						blkMaxLen1s[blk] = len1s;
						blkMaxEnds1s[blk] = pos;
					}
				} else {
					len1s = 0;
				}
			}
			for (u32 k = 0; k < blkSize && arr[blk * blkSize + k] == 1 && (blk * blkSize + k - 1 < 0
						|| arr[blk * blkSize + k - 1] == 1); k++) {
				blkLeftLens1s[blk]++;
			}
			for (u32 k = blkSize - 1; k >= 0 && arr[blk * blkSize + k] == 1 && (blk * blkSize + k + 1 >= n
						|| arr[blk * blkSize + k + 1] == 1); k--) {
				blkRightLens1s[blk]++;
			}
		}
	}
	return 0;
}