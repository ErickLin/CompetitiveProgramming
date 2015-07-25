/*
ID: Jugglebrosjr2
LANG: C++
TASK: fencing
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

long long sign(long long num) {
	return (num > 0) - (num < 0);
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	ifstream fin("fencing.in");
	ofstream fout("fencing.out");
	unsigned long long n, q;
	fin >> n >> q;
	long long minX = 1000000000, maxX = -1000000000, minY = 1000000000, maxY = -1000000000;
	vector<pair<long long, long long> > pos(n + q);
	for (unsigned long long i = 0; i < n; i++) {
		long long x, y;
		fin >> x >> y;
		if (x < minX) {
			minX = x;
		}
		if (x > maxX) {
			maxX = x;
		}
		if (y < minY) {
			minY = y;
		}
		if (y > maxY) {
			maxY = y;
		}
		pos[i] = make_pair(x, y);
	}
	long long numCows = n;
	for (unsigned long long i = 0; i < q; i++) {
		unsigned long long queryType;
		fin >> queryType;
		if (queryType == 1) {
			long long x, y;
			fin >> x >> y;
			if (x < minX) {
				minX = x;
			}
			if (x > maxX) {
				maxX = x;
			}
			if (y < minY) {
				minY = y;
			}
			if (y > maxY) {
				maxY = y;
			}
			pos[numCows++] = make_pair(x, y);
		} else {
			long long a, b, c;
			fin >> a >> b >> c;
			if (a == 0) {
				long long y = c / b;
				if (c % b == 0) {
					if (y >= minY && y <= maxY) {
						fout << "NO\n";
					} else {
						fout << "YES\n";
					}
				} else {
					if (y >= minY && y < maxY) {
						fout << "NO\n";
					} else {
						fout << "YES\n";
					}
				}
			} else if (b == 0) {
				long long x = c / a;
				if (c % a == 0) {
					if (x >= minX && x <= maxX) {
						fout << "NO\n";
					} else {
						fout << "YES\n";
					}
				} else {
					if (x >= minX && x < maxX) {
						fout << "NO\n";
					} else {
						fout << "YES\n";
					}
				}
			} else {
				long long x = pos[0].first;
				long long y = pos[0].second;
				long long side = sign((a * x + b * y - c) * sign(b));
				bool sameSide = true;
				for (long long i = 1; i < numCows && sameSide; i++) {
					x = pos[i].first;
					y = pos[i].second;
					if (sign((a * x + b * y - c) * sign(b)) != side) {
						sameSide = false;
						fout << "NO\n";
					}
				}
				if (sameSide) {
					fout << "YES\n";
				}
			}
		}
	}
	//fout << minX << " " << maxX << " " << minY << " " << maxY << '\n';
    return 0;
}