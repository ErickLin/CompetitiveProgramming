#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef set<int> si;

void print(set<ll>& del_pos, map<ll, list<char>>& ins_pos) {
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
  vector<set<ll>> del_pos(2);
  // Positions in the original string where new characters are inserted.
  vector<map<ll, list<char>>> ins_pos(2);
  forf(i, 2) {
    char instruction;
    cin >> instruction;
    while (instruction != 'E') {
      ll pos;
      cin >> pos;
      ll orig_pos = pos;
      // used to keep track of how many deleted elements we have counted toward orig_pos
      auto del_it = del_pos[i].begin();
      if (instruction == 'D') {
        bool make_new_pos = true;
        for (auto& kv : ins_pos[i]) {
          ll elem_pos = kv.first;
          int count = kv.second.size();
          if (orig_pos < elem_pos) {
            break;
          }
          if (orig_pos >= elem_pos + count) {
            orig_pos -= count;
          } else {
            make_new_pos = false;
            auto it = kv.second.begin();
            advance(it, orig_pos - elem_pos);
            kv.second.erase(it);
            if (kv.second.empty()) {
              ins_pos[i].erase(elem_pos);
            }
            break;
          }
          int num_del_smaller = distance(del_it, del_pos[i].upper_bound(elem_pos));
          del_it = del_pos[i].upper_bound(elem_pos);
          orig_pos += num_del_smaller;
        }
        int num_del_smaller = distance(del_it, del_pos[i].upper_bound(orig_pos));
        while (num_del_smaller) {
          del_it = del_pos[i].upper_bound(orig_pos);
          orig_pos += num_del_smaller;
          num_del_smaller = distance(del_it, del_pos[i].upper_bound(orig_pos));
        }
        if (make_new_pos) {
          del_pos[i].insert(orig_pos);
        }
      } else {
        char new_char;
        cin >> new_char;
        bool make_new_pos = true;
        for (auto& kv : ins_pos[i]) {
          ll elem_pos = kv.first;
          int count = kv.second.size();
          int num_del_smaller = distance(del_it, del_pos[i].lower_bound(elem_pos));
          del_it = del_pos[i].lower_bound(elem_pos);
          orig_pos += num_del_smaller;
          if (orig_pos <= elem_pos) {
            break;
          }
          if (orig_pos > elem_pos + count) {
            orig_pos -= count;
          } else {
            make_new_pos = false;
            if (orig_pos == elem_pos + count) {
              kv.second.push_back(new_char);
            } else {
              auto it = kv.second.begin();
              advance(it, orig_pos - elem_pos);
              kv.second.insert(it, new_char);
            }
            break;
          }
        }
        int num_del_smaller = distance(del_it, del_pos[i].lower_bound(orig_pos));
        while (num_del_smaller) {
          del_it = del_pos[i].lower_bound(orig_pos);
          orig_pos += num_del_smaller;
          num_del_smaller = distance(del_it, del_pos[i].lower_bound(orig_pos));
        }
        if (make_new_pos) {
          ins_pos[i][orig_pos].push_front(new_char);
        }
      }
      cin >> instruction;
      //print(del_pos[i], ins_pos[i]);
    }
    //cout << '\n';
  }

  cout << !(del_pos[0] == del_pos[1] && ins_pos[0] == ins_pos[1]) << '\n';
}
