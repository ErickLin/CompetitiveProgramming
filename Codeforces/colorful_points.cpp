// 909D
#include <iostream>
#include <list>
using namespace std;
#define mp make_pair
#define pb push_back

int main() {
  string s;
  cin >> s;
  list<pair<int, char>> chains;
  int chain_len = 0;
  char prev = '\0';
  for (char c : s) {
    if (c != prev && chain_len > 0) {
      chains.pb(mp(chain_len, prev));
      chain_len = 0;
    }
    chain_len++;
    prev = c;
  }
  chains.pb(mp(chain_len, prev));
  int moves;
  for (moves = 0; chains.size() > 1; moves++) {
    //cout << chains.size() << '\n';
    for (auto it = chains.begin(); it != chains.end(); it++) {
      //cout << it->first << ' ';
      --it->first;
      if (it != chains.begin() && next(it) != chains.end()) {
        --it->first;
      }
    }
    for (auto it = chains.begin(); it != chains.end();) {
      if (it->first <= 0) {
        it = chains.erase(it);
      } else {
        it++;
      }
    }
    for (auto it = chains.begin(); it != chains.end();) {
      if (next(it) == chains.end()) {
        break;
      }
      auto it2 = next(it);
      if (it->second == it2->second) {
        it->first += it2->first;
        chains.erase(it2);
      } else {
        it++;
      }
    }
    //cout << '\n';
  }
  cout << moves << '\n';
}
