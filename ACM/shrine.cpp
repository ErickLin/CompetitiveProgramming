#include <algorithm>
#include <cstdio>
#include <iostream>
#include <math.h>
#include <queue>
#include <set>
#include <vector>

using namespace std;
const double pi = 3.14159;
const int r = 1000;

int main(int argc, char** argv) {
	int w, n, d;
	cin >> w >> n >> d;
	while (w != 0) {
		set<int> shrines;
		for (int i = 0; i < d; i++) {
			int factor;
			cin >> factor;
			for (int mult = 1; factor * mult <= n; mult++) {
				shrines.insert(factor * mult);
			}
		}
		vector<double> dist(n);
		int prevShrine = 0;
		int i = 0;
		for (set<int>::iterator itr = shrines.begin(); itr != shrines.end(); itr++) {
    		double theta = (*itr - prevShrine) * 2.0 * pi / 12.0;
    		dist[i] = 2.0 * r * sin(theta / 2);
    		cout << *itr << " " << prevShrine << " " << dist[i] << '\n';
    		prevShrine = *itr;
    		i++;
		}
		for (i = 0; i < 12; i++) {
			//cout << dist[i] << '\n';
		}
		cin >> w;
		if (w > 0) {
			cin >> n >> d;
		} else {
			break;
		}
	}
}