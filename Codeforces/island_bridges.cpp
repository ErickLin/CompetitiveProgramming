#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

int compare(pair<pair<u64, u64>, int> a, pair<pair<u64, u64>, int> b) {
	if (a.first.first == b.first.first) {
		return a.first.second < b.first.second;
	}
	return a.first.first < b.first.first;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<u64> l(n), r(n);
	// first element is the interval, second element is the index
	vector<pair<pair<u64, u64>, int> > intervals(n - 1);
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		if (i > 0) {
			intervals[i - 1] = make_pair(make_pair(l[i] - r[i - 1], r[i] - l[i - 1]), i - 1);
		}
	}
	sort(intervals.begin(), intervals.end(), &compare);
	map<u64, stack<int> > a;
	for (int i = 0; i < m; i++) {
		u64 temp;
		cin >> temp;
		a[temp].push(i);
	}
	vector<int> ans(n);
	for (int i = n - 2; i >= 0; i--) {
		map<u64, stack<int> >::iterator it = a.upper_bound(intervals[i].first.second);
		if (it == a.begin()) {
			cout << "No\n";
			return 0;
		}
		it--;
		if (it->first < intervals[i].first.first) {
			cout << "No\n";
			return 0;
		} else {
			ans[intervals[i].second] = it->second.top();
			it->second.pop();
			if (it->second.empty()) {
				a.erase(it->first);
			}
		}
	}
	cout << "Yes\n";
	cout << ans[0] + 1;
	for (int i = 1; i < n - 1; i++) {
		cout << ' ' << (ans[i] + 1);
	}
	cout << '\n';
	return 0;
}