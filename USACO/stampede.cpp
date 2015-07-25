/*
ID: Jugglebrosjr2
LANG: C++
TASK: stampede
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    freopen("stampede.in", "r", stdin);
    freopen("stampede.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<int, int> > cows;
    for (int i = 0; i < n; i++) {
    	int x, y, r;
    	cin >> x >> y >> r;
    	cows.push_back(make_pair((-x - 1) * r, y));
    	//negative value for y indicates end of interval
    	cows.push_back(make_pair(-x * r, -y));
    }
    sort(cows.begin(), cows.end());
    set<int> canSee;
    set<int> remaining;
    for (int i = 0; i < cows.size(); ) {
    	int j;
    	for (j = i; j < cows.size() && cows[i].first == cows[j].first; j++) {
    		//if beginning of interval
    		if (cows[j].second > 0) {
    			remaining.insert(cows[j].second);
    		} else {
    			remaining.erase(-cows[j].second);
    		}
    	}
    	if (!remaining.empty()) {
    		canSee.insert(*remaining.begin());
    	}
    	i = j;
    }
    cout << canSee.size() << endl;
    return 0;
}