#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    //freopen("wet.txt", "r", stdin);
	int x, y, t, l, w;
	cin >> x >> y >> t >> l >> w;
	for (int s = 1; x != -1; s++) {
		vector<vector<int> > label(x, vector<int>(y));
		vector<vector<bool> > wall(x, vector<bool>(y));
		vector<pair<int, int> > leaks;
		for (int i = 0; i < l; i++) {
			int loc1, loc2;
			cin >> loc1 >> loc2;
			loc1--;
			loc2--;
			leaks.push_back(make_pair(loc1, loc2));
		}
		for (int i = 0; i < w; i++) {
			int start1, start2;
			cin >> start1 >> start2;
			start1--;
			start2--;
			int end1, end2;
			cin >> end1 >> end2;
			end1--;
			end2--;
			if (start1 == end1) {
				for (int loc2 = min(start2, end2); loc2 <= max(start2, end2); loc2++) {
					wall[start1][loc2] = true;
				}
			} else if (start2 == end2) {
				for (int loc1 = min(start1, end1); loc1 <= max(start1, end1); loc1++) {
					wall[loc1][start2] = true;
				}
			} else {
				int xOffset = 0;
				int yOffset = 0;
				int loc1 = start1;
				int loc2 = start2;
				while (true) {
					wall[loc1][loc2] = true;
					if (loc1 == end1)
						break;
					if (end1 > loc1) {
						loc1++;
					} else {
						loc1--;
					}
					if (end2 > loc2) {
						loc2++;
					} else {
						loc2--;
					}
				}
			}
		}
		for (int i = 0; i < leaks.size(); i++) {
			label[leaks[i].first][leaks[i].second] = 1;
			queue<pair<int, int> > q;
			q.push(leaks[i]);
			while (!q.empty()) {
				pair<int, int> loc = q.front();
				q.pop();
				vector<pair<int, int> > neighbors;
				if (loc.first > 0) {
					neighbors.push_back(make_pair(loc.first - 1, loc.second));
				}
				if (loc.first < x - 1) {
					neighbors.push_back(make_pair(loc.first + 1, loc.second));
				}
				if (loc.second > 0) {
					neighbors.push_back(make_pair(loc.first, loc.second - 1));
				}
				if (loc.second < x - 1) {
					neighbors.push_back(make_pair(loc.first, loc.second + 1));
				}
				for (int i = 0; i < neighbors.size(); i++) {
					if ((label[neighbors[i].first][neighbors[i].second] > label[loc.first][loc.second] + 1
							|| label[neighbors[i].first][neighbors[i].second] == 0)
							&& !wall[neighbors[i].first][neighbors[i].second]) {
						label[neighbors[i].first][neighbors[i].second] = label[loc.first][loc.second] + 1;
						if (label[neighbors[i].first][neighbors[i].second] < t)
							q.push(make_pair(neighbors[i].first, neighbors[i].second));
					}
				}
			}
		}
		int count = 0;
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				if (label[i][j] > 0) {
					//cout << i << " " << j << " " << label[i][j] << '\n';
					count++;
				}
			}
		}
		cout << count << '\n';
		//cout << '\n';
		cin >> x >> y >> t >> l >> w;
	}
    return 0;
}
