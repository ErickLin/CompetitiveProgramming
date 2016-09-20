#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

void recurse(int probNum, vi &ownerOf, vi &lastEndTimes, int penalty, int *highest, int *minPenalty, vi &bestOwnerOf, int k, vi &ts) {
    if (probNum == k) {
        if (k > *highest) {
            *highest = k;
            *minPenalty = penalty;
            bestOwnerOf = ownerOf;
        } else if (k == *highest && penalty < *minPenalty) {
            *minPenalty = penalty;
            bestOwnerOf = ownerOf;
        }
    } else {
        bool canAdd = false;
        for (int i = 0; i < 3; i++) {
            if (i == 1 && lastEndTimes[1] == lastEndTimes[0]) {
                continue;
            }
            if (i == 2 && lastEndTimes[2] == lastEndTimes[0] && lastEndTimes[2] == lastEndTimes[1]) {
                continue;
            }
            lastEndTimes[i] += ts[probNum];
            if (lastEndTimes[i] <= 300) {
                canAdd = true;
                ownerOf[probNum] = i;
                recurse(probNum + 1, ownerOf, lastEndTimes, penalty + lastEndTimes[i], highest, minPenalty, bestOwnerOf, k, ts);
                ownerOf[probNum] = 0;
            }
            lastEndTimes[i] -= ts[probNum];
        }
        if (!canAdd) {
            if (probNum > *highest) {
                *highest = probNum;
                *minPenalty = penalty;
                bestOwnerOf = ownerOf;
            } else if (probNum == *highest && penalty < *minPenalty) {
                *minPenalty = penalty;
                bestOwnerOf = ownerOf;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int t = 1; t <= n; t++) {
        int k;
        cin >> k;
        vi ts(k);
        map<int, vc> labels;
        map<char, int> labelToTime;
        for (int i = 0; i < k; i++) {
            cin >> ts[i];
            labels[ts[i]].push_back('A' + i);
            labelToTime['A' + i] = ts[i];
        }
        for (auto it = labels.begin(); it != labels.end(); it++) {
            sort(it->second.rbegin(), it->second.rend());
        }
        sort(ts.begin(), ts.end());

        int highest = 0;
        int minPenalty = INT_MAX;
        vi bestOwnerOf(k);

        vi ownerOf(k);
        ownerOf[0] = 0;
        vi lastEndTimes(3);
        lastEndTimes[0] = ts[0];
        recurse(1, ownerOf, lastEndTimes, lastEndTimes[0], &highest, &minPenalty, bestOwnerOf, k, ts);

        vector<pair<int, pii> > order1(highest);
        vi prefixEndTimes(3);
        for (int i = 0; i < highest; i++) {
            prefixEndTimes[bestOwnerOf[i]] += ts[i];
            order1[i] = make_pair(prefixEndTimes[bestOwnerOf[i]], make_pair(ts[i], bestOwnerOf[i]));
        }
        sort(order1.begin(), order1.end());
        vector<pair<int, pair<char, int> > > order2(highest);
        vector<map<char, int> > orderByOwner(3);
        fill(lastEndTimes.begin(), lastEndTimes.end(), 0);
        for (int i = 0; i < highest; i++) {
            int endTime = order1[i].first;
            char label = labels[order1[i].second.first].back();
            labels[order1[i].second.first].pop_back();
            int owner = order1[i].second.second;
            order2[i] = make_pair(endTime, make_pair(label, owner));
            orderByOwner[owner][label] = orderByOwner[owner].size();
            lastEndTimes[owner] = max(lastEndTimes[owner], endTime);
            pair<int, char> a = make_pair(owner, orderByOwner[owner][label]);
        }
        sort(order2.begin(), order2.end());
        /*
        cout << '\n';
        for (int i = 0; i < highest; i++) {
            int endTime = order2[i].first;
            char label = order2[i].second.first;
            int owner = order2[i].second.second;
            cout << label << owner << '[' << orderByOwner[owner][label] << ']' << endTime << ' ';
        }
        cout << '\n';
        */
        vector<pair<char, int> > order3(highest);
        for (int i = 0; i < highest; i++) {
            order3[i] = make_pair(order2[i].second.first, order2[i].second.second);
        }
        for (int i = 0; i < highest; i++) {
            for (int j = i + 1; j < highest; j++) {
                char labelI = order3[i].first;
                int ownerI = order3[i].second;
                char labelJ = order3[j].first;
                int ownerJ = order3[j].second;
                if (ownerI == ownerJ && orderByOwner[ownerI][labelI] == orderByOwner[ownerJ][labelJ]) {
                    cout << "here\n";
                }
                // Swap two problems between owners
                if (ownerI != ownerJ && orderByOwner[ownerI].size() - orderByOwner[ownerI][labelI] == orderByOwner[ownerJ].size() - orderByOwner[ownerJ][labelJ]
                        && labelI > labelJ
                        && lastEndTimes[ownerI] + labelToTime[labelJ] - labelToTime[labelI] <= 300
                        && lastEndTimes[ownerJ] + labelToTime[labelI] - labelToTime[labelJ] <= 300) {
                    orderByOwner[ownerI][labelJ] = orderByOwner[ownerI][labelI];
                    orderByOwner[ownerJ][labelI] = orderByOwner[ownerJ][labelJ];
                    orderByOwner[ownerI].erase(labelI);
                    orderByOwner[ownerJ].erase(labelJ);
                    lastEndTimes[ownerI] += labelToTime[labelJ] - labelToTime[labelI];
                    lastEndTimes[ownerJ] += labelToTime[labelI] - labelToTime[labelJ];
                    //cout << "(" << order3[i].first << ", " << order3[j].first << ")<->";
                    char temp = labelI;
                    order3[i].first = labelJ;
                    order3[j].first = temp;
                    //cout << "(" << order3[i].first << ", " << order3[j].first << ")\n";
                }
            }
        }

        //vi penaltyTimes(3);
        //int penalty = 0;
        cout << "Data set " << t << ": ";
        for (int i = 0; i < highest; i++) {
            char label = order3[i].first;
            int owner = order3[i].second;
            //penaltyTimes[owner] += labelToTime[label];
            //penalty += penaltyTimes[owner];
            cout << label << ' ';
        }
        cout << highest << ' ' << minPenalty << '\n';
        /*
        if (penalty != minPenalty) {
            cout << "Wrong answer\n";
        }
        */
    }
    return 0;
}
