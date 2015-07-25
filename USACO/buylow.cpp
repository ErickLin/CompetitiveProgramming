/*
ID: Jugglebrosjr2
LANG: C++
TASK: buylow
*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define BIGINT_LEN 99

using namespace std;
typedef unsigned int u32;
typedef vector<unsigned short> bigint;
ifstream fin("buylow.in");
ofstream fout("buylow.out");

bigint convert(u32 b) {
	bigint ret(BIGINT_LEN);
	for (int i = BIGINT_LEN - 1; i >= 0; i--) {
		ret[i] = b % 10;
		b /= 10;
	}
	return ret;
}

bigint add(bigint a, u32 b) {
	bigint ret(BIGINT_LEN);
	unsigned short carry = 0;
	for (int i = BIGINT_LEN - 1; i >= 0; i--) {
		ret[i] = (a[i] + b % 10 + carry) % 10;
		carry = (a[i] + b % 10 + carry) / 10;
		b /= 10;
	}
	return ret;
}

bigint add(bigint a, bigint b) {
	bigint ret(BIGINT_LEN);
	unsigned short carry = 0;
	for (int i = BIGINT_LEN - 1; i >= 0; i--) {
		ret[i] = (a[i] + b[i] + carry) % 10;
		carry = (a[i] + b[i] + carry) / 10;
	}
	return ret;
}

bigint subtract(bigint a, bigint b) {
	bigint ret(BIGINT_LEN);
	unsigned short carry = 0;
	for (int i = BIGINT_LEN - 1; i >= 0; i--) {
		if (b[i] + carry > a[i]) {
			ret[i] = 10 + a[i] - b[i] - carry;
			carry = 1;
		} else {
			ret[i] = a[i] - b[i] - carry;
			carry = 0;
		}
	}
	return ret;
}

string toString(bigint a) {
	bool leading = true;
	string s = "";
	for (size_t i = 0; i < a.size(); i++) {
		if (leading && a[i] != 0) {
			leading = false;
		}
		if (!leading) {
			s += a[i] + '0';
		}
	}
	return s;
}

int main(int argc, char** argv) {
    u32 n;
    fin >> n;
    vector<u32> arr(n);
    for (u32 i = 0; i < n; i++) {
    	fin >> arr[i];
    }
    //length of longest decreasing subsequence in prefix up to index
    vector<u32> dp(n);
    //number of times LDS appears in prefix up to index
    vector<bigint> count(n);
    for (u32 i = 0; i < n; i++) {
    	dp[i] = 1;
    	//maintains count for all values of second-to-last element
    	map<u32, bigint*> prevOcc;
    	for (u32 j = 0; j < i; j++) {
    		if (arr[j] > arr[i]) {
    			if (dp[j] + 1 > dp[i]) {
    				dp[i] = dp[j] + 1;
    				//count[i] = count[j];
    				prevOcc.clear();
    			}
    			if (dp[j] + 1 == dp[i]) {
    				//if (prevOcc.count(arr[j])) {
    				//	count[i] = subtract(count[i], prevOcc[arr[j]]);
    				//}
    				//count[i] = add(count[i], count[j]);
    				prevOcc[arr[j]] = &count[j];
    			}
    		}
    	}
    	if (prevOcc.empty()) {
    		count[i] = convert(1);
    	} else {
    		count[i] = convert(0);
    		for (map<u32, bigint*>::iterator it = prevOcc.begin(); it != prevOcc.end(); it++) {
    			count[i] = add(count[i], *(it -> second));
    		}
    	}
    	//cout << arr[i] << ' ' << dp[i] << ' ' << count[i] << '\n';
    }
    u32 maxLen = 1;
    bigint totalCount = convert(0);
	//maintains count for all values of last element
	map<u32, bigint> prevOcc;
    for (u32 i = 0; i < n; i++) {
		if (dp[i] > maxLen) {
			maxLen = dp[i];
			totalCount = count[i];
			prevOcc.clear();
			prevOcc[arr[i]] = count[i];
		} else if (dp[i] == maxLen) {
			if (prevOcc.count(arr[i])) {
				totalCount = subtract(totalCount, prevOcc[arr[i]]);
			}
			totalCount = add(totalCount, count[i]);
			prevOcc[arr[i]] = count[i];
		}
    }
    fout << maxLen << ' ' << toString(totalCount) << '\n';
    return 0;
}