#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    int n = stoi(line);
    vector<string> cityNames;
    vector<string> tagNames;
    map<string, set<string> > tagsByCityTemp;
    //only use to keep track of which tags we have seen for now
    map<string, int> tagIndices;
    while (getline(cin, line)) {
        string city = "";
        int colonPos = -1;
        for (int i = 0; i < line.size() && colonPos == -1; i++) {
            if (line[i] == ':') {
                colonPos = i;
            } else {
                city += line[i];
            }
        }
        cityNames.push_back(city);
        string tag = "";
        for (int i = colonPos + 1; i < line.size(); i++) {
            if (line[i] == ',') {
                tagsByCityTemp[city].insert(tag);
                if (tagIndices.find(tag) == tagIndices.end()) {
                    tagIndices[tag] = tagNames.size();
                    tagNames.push_back(tag);
                    tagsByCityTemp[city].insert(tag);
                }
                tag = "";
            } else {
                tag += line[i];
            }
        }
        if (tag != "") {
            tagsByCityTemp[city].insert(tag);
            if (tagIndices.find(tag) == tagIndices.end()) {
                tagIndices[tag] = tagNames.size();
                tagNames.push_back(tag);
                tagsByCityTemp[city].insert(tag);
            }
        }
    }
    sort(cityNames.begin(), cityNames.end());
    sort(tagNames.begin(), tagNames.end());
    map<string, int> cityIndices;
    for (int i = 0; i < cityNames.size(); i++) {
        cityIndices[cityNames[i]] = i;
    }
    //now use tag indices to keep track of tags in alphabetical order
    for (int i = 0; i < tagNames.size(); i++) {
        tagIndices[tagNames[i]] = i;
    }
    map<int, set<int> > tagsByCity;
    map<int, set<int> > citiesByTag;
    for (auto itC = tagsByCityTemp.begin(); itC != tagsByCityTemp.end(); itC++) {
        for (auto itT = itC->second.begin(); itT != itC->second.end(); itT++) {
            tagsByCity[cityIndices[itC->first]].insert(tagIndices[*itT]);
            citiesByTag[tagIndices[*itT]].insert(cityIndices[itC->first]);
        }
    }
    /*
    //print matching cities by tag
    for (auto it = citiesByTag.begin(); it != citiesByTag.end(); it++) {
        cout << tagNames[it->first] << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << cityNames[*it2] << ' ';
        }
        cout << '\n';
    }
    */
    /*
    map<set<int>, set<int> > groups;
    for (int i = 0; i < tagNames.size(); i++) {
        for (int j = 0; j < tagNames.size(); j++) {
            if (j != i) {
                vector<int> inter;
                set_intersection(citiesByTag[i].begin()
                        , citiesByTag[i].end(), citiesByTag[j].begin()
                        , citiesByTag[j].end(), back_inserter(inter));
                set<int> jointCities;
                for (int i = 0; i < inter.size(); i++) {
                    jointCities.insert(inter[i]);
                }
                if (jointCities.size() >= 2) {
                    groups[jointCities].insert(i);
                    groups[jointCities].insert(j);
                }
            }
        }
    }
    */
    map<set<int>, set<int> > groupsInv;
    for (int i = 0; i < cityNames.size(); i++) {
        for (int j = 0; j < cityNames.size(); j++) {
            if (j != i) {
                vector<int> inter;
                set_intersection(tagsByCity[i].begin()
                        , tagsByCity[i].end(), tagsByCity[j].begin()
                        , tagsByCity[j].end(), back_inserter(inter));
                set<int> jointTags;
                for (int i = 0; i < inter.size(); i++) {
                    jointTags.insert(inter[i]);
                }
                if (jointTags.size() >= n) {
                    groupsInv[jointTags].insert(i);
                    groupsInv[jointTags].insert(j);
                }
            }
        }
    }
    for (auto it = groupsInv.begin(); it != groupsInv.end(); it++) {
        for (int i = 0; i < cityNames.size(); i++) {
            bool containsAll = true;
            for (auto itT = it->first.begin(); itT != it->first.end() && containsAll; itT++) {
                if (tagsByCity[i].find(*itT) == tagsByCity[i].end()) {
                    containsAll = false;
                }
            }
            if (containsAll) {
                groupsInv[it->first].insert(i);
            }
        }
    }
    //contains groups in string form along with number of tags for each group
    vector<pair<string, int> > ans;
    /*
    for (auto it = groups.begin(); it != groups.end(); it++) {
        auto itC = it->first.begin();
        cout << cityNames[*itC];
        itC++;
        while (itC != it->first.end()) {
            cout << ',' << cityNames[*itC];
            itC++;
        }
        cout << ':';
        auto itT = it->second.begin();
        cout << tagNames[*itT];
        itT++;
        while (itT != it->second.end()) {
            cout << ',' << tagNames[*itT];
            itT++;
        }
        cout << '\n';
    }
    */
    for (auto it = groupsInv.begin(); it != groupsInv.end(); it++) {
        string c = "";
        auto itC = it->second.begin();
        c += cityNames[*itC];
        itC++;
        while (itC != it->second.end()) {
            c += ',' + cityNames[*itC];
            itC++;
        }
        c += ':';
        auto itT = it->first.begin();
        c += tagNames[*itT];
        itT++;
        while (itT != it->first.end()) {
            c += ',' + tagNames[*itT];
            itT++;
        }
        ans.push_back(make_pair(c, it->first.size()));
    }
    sort(ans.begin(), ans.end(), [](pair<string, int> a, pair<string, int> b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    });
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << '\n';
    }
}
