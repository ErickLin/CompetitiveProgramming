#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;
u64 MOD = 1000000007;

typedef struct Interval {
	u64 total;
	u32 a, b;
	struct Interval* left;
	struct Interval* right;
} Interval;

void constructTree(Interval* node) {
	if (node->a < node->b) {
		u32 mid = node->a + ((node->b - node->a) >> 1);
		node->left = (Interval*) malloc(sizeof(struct Interval));
		node->left->total = 0;
		node->left->a = node->a;
		node->left->b = mid;
		constructTree(node->left);
		node->right = (Interval*) malloc(sizeof(struct Interval));
		node->right->total = 0;
		node->right->a = mid + 1;
		node->right->b = node->b;
		constructTree(node->right);
	} else {
		node->left = NULL;
		node->right = NULL;
	}
}

u64 sum(u32 len) {
	return (len * (len + 1) * (len + 2) / 3) % MOD;
}

void propagate(Interval* node, u32 a, u32 b) {
	if (node->a <= a && node->b >= b) {
		node->total = (node->total + sum(b - a + 1)) % MOD;
		if (node->a < node->b) {
			propagate(node->left, a, b);
			propagate(node->right, a, b);
		}
	} else if (node->a > a && node->a <= b) {
		node->total = (node->total + sum(min(b, node->b) - a + 1) - sum(node->a - a)) % MOD;
		if (node->a < node->b) {
			propagate(node->left, a, b);
			propagate(node->right, a, b);
		}
	} else if (node->b < b && node->b >= a) {
		node->total = (node->total + sum(node->b - a + 1)) % MOD;
		if (node->a < node->b) {
			propagate(node->left, a, b);
			propagate(node->right, a, b);
		}
	}
}

u64 calcSum(Interval* node, u32 a, u32 b) {
	if (node->a >= a && node->b <= b) {
		return node->total;
	} else if (node->a > b || node->b < a) {
		return 0;
	} else {
		u64 total = 0;
		if (node->left != NULL)
			total += calcSum(node->left, a, b);
		if (node->right != NULL) {
			total += calcSum(node->right, a, b);
		}
		total %= MOD;
		return total;
	}
}

int main() {
	u32 n, q;
	cin >> n >> q;
	Interval temp;
	Interval* root = (Interval*) malloc(sizeof(struct Interval));
	root->total = 0;
	root->a = 0;
	root->b = n - 1;
	constructTree(root);
	for (u32 i = 0; i < q; i++) {
		u32 type, x, y;
		cin >> type >> x >> y;
		x--;
		y--;
		if (type == 1) {
			propagate(root, x, y);
		} else {
			cout << calcSum(root, x, y) << '\n';
		}
	}
	return 0;
}