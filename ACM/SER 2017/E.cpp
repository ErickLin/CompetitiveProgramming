#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define pb push_back
typedef long long ll;
typedef set<ll> sll;
 
void print(sll& del_pos, map<ll, list<char>>& ins_pos) {
  cout << "del: ";
  for (ll l : del_pos) {
    cout << l << ' ';
  }
  cout << " ... ";
  for (const auto& kv : ins_pos) {
    cout << "ins: ";
    cout << kv.first << ": ";
    for (const auto& c : kv.second) {
      cout << c << ' ';
    }
    cout << ", ";
  }
  cout << '\n';
}
 
int main() {
  // Positions of characters in the original string that end up deleted.
  vector<sll> del_pos(2);
  // Ordered lists of newly inserted characters at each position in the
  // original string.
  vector<map<ll, list<char>>> ins_pos(2);
  vector<sll> all_pos(2);
  forf(i, 2) {
    char instruction;
    cin >> instruction;
    while (instruction != 'E') {
      ll pos;
      cin >> pos;
      // Will become processed as the position in the original string.
      ll orig_pos = pos;
      if (instruction == 'I') {
        char new_char;
        cin >> new_char;
        bool create_at_orig_pos = true;
        for (ll elem_pos : all_pos[i]) {
          if (orig_pos < elem_pos) {
            break;
          }
          if (ins_pos[i].count(elem_pos)) {
            int count = ins_pos[i][elem_pos].size();
            if (orig_pos > elem_pos + count) {
              orig_pos -= count;
            } else {
              create_at_orig_pos = false;
              if (orig_pos == elem_pos + count) {
                ins_pos[i][elem_pos].push_back(new_char);
              } else {
                auto it = ins_pos[i][elem_pos].begin();
                advance(it, orig_pos - elem_pos);
                ins_pos[i][elem_pos].insert(it, new_char);
              }
              break;
            }
          }
          if (orig_pos == elem_pos) {
            break;
          }
          if (del_pos[i].count(elem_pos)) {
            orig_pos++;
          }
        }
        if (create_at_orig_pos) {
          ins_pos[i][orig_pos].push_front(new_char);
          all_pos[i].insert(orig_pos);
        }
      } else /* if (instruction == 'D') */ {
        bool create_at_orig_pos = true;
        for (ll elem_pos : all_pos[i]) {
          if (orig_pos < elem_pos) {
            break;
          }
          if (ins_pos[i].count(elem_pos)) {
            int count = ins_pos[i][elem_pos].size();
            if (orig_pos >= elem_pos + count) {
              orig_pos -= count;
            } else {
              create_at_orig_pos = false;
              auto it = ins_pos[i][elem_pos].begin();
              advance(it, orig_pos - elem_pos);
              ins_pos[i][elem_pos].erase(it);
              if (ins_pos[i][elem_pos].empty()) {
                ins_pos[i].erase(elem_pos);
                if (!del_pos[i].count(elem_pos)) {
                  all_pos[i].erase(elem_pos);
                }
              }
              break;
            }
          }
          if (del_pos[i].count(elem_pos)) {
            orig_pos++;
          }
        }
        if (create_at_orig_pos) {
          del_pos[i].insert(orig_pos);
          all_pos[i].insert(orig_pos);
        }
      }
      cin >> instruction;
    }
    for (auto it = ins_pos[i].rbegin(); it != ins_pos[i].rend();) {
      auto it2 = next(it);
      if (it2 == ins_pos[i].rend()) {
        break;
      }
      if (del_pos[i].count(it2->first) && del_pos[i].count(it->first)) {
        for (const auto& elem : it->second) {
          ins_pos[i][it2->first].pb(elem);
        }
        advance(it, 1);
        ins_pos[i].erase(it.base());
      } else {
        it++;
      }
    }
  }
  cout << !(del_pos[0] == del_pos[1] && ins_pos[0] == ins_pos[1]) << '\n';
}
