#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

struct Node {
	u64 data = 0, dataSum = 0;
	set<u32> children;
} Node;

u64 getDataSum(Node* node) {
	node->dataSum = node->data;
	for (set<u32>::iterator it = node->children.begin(); it != node->children.end(); it++) {
		node->dataSum += (*it)->data;
		getDataSum(*it);
	}
	return node->dataSum;
}

int main() {
	u32 n;
	cin >> n;
	vector<set<u32> > edges(n);
	for (u32 i = 0; i < n - 1; i++) {
		u32 a, b;
		cin >> a-- >> b--;
		edges[a].insert(b);
	}
	return 0;
}