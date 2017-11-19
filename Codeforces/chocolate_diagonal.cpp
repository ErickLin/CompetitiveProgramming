// 555C
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
struct SegTree {
	public:
		int a, b, min;
		SegTree* left = NULL;
		SegTree* right = NULL;
		SegTree(int a, int b, int min);
		updateMin(int newMin);
};

SegTree::SegTree(int a, int b, int min) {
	this->a = a;
	this->b = b;
	this->min = min;
	if (a < b) {
		SegTree* left = new SegTree(a, a + ((b - a) >> 1), min);
		SegTree* right = new SegTree(a + ((b - a) >> 1) + 1, b, min);
	}
}

SegTree::updateMin(int newMin) {

}
*/

int main() {
	int n;
	cin >> n;
	/*
	SegTree* hor = new SegTree(0, n - 1, -1);
	SegTree* vert = new SegTree(0, n - 1, -1);
	*/
	int q;
	cin >> q;
	// maps each x-value to a pair containing a direction along with:
	// the minimum-value column reached if direction is left
	// the minimum-value row reached if direction is up
	map<int, pair<char, int> > m;
	m[-1] = make_pair('U', 0);
	m[n] = make_pair('L', 0);
	for (int i = 0; i < q; i++) {
		int x, y;
		char dir;
		cin >> x >> y >> dir;
		x--;
		y--;
		//if x has not already been queried before
		if (m.find(x) == m.end()) {
			map<int, pair<char, int> >::iterator it = m.upper_bound(x);
			//cout << it->first << ' ' << it->second.first << ' ' << it->second.second << '\n';
			if (dir == 'L') {
				it--;
				//cout << it->first << ' ' << it->second.first << ' ' << it->second.second << '\n';
				if (it->second.first == 'L') {
					m[x] = make_pair('L', it->second.second);
				} else {
					if (it->first >= 0 && it->first < n) {
						m[x] = make_pair('L', it->first + 1);
					} else {
						m[x] = make_pair('L', 0);
					}
				}
				cout << x - m[x].second + 1 << '\n';
			} else {
				//cout << it->first << ' ' << it->second.first << ' ' << it->second.second << '\n';
				if (it->second.first == 'L') {
					if (it->first >= 0 && it->first < n) {
						m[x] = make_pair('U', n - it->first);
					} else {
						m[x] = make_pair('U', 0);
					}
				} else {
					m[x] = make_pair('U', it->second.second);
				}
				cout << y - m[x].second + 1 << '\n';
			}
		} else {
			cout << "0\n";
		}
	}
	return 0;
}
