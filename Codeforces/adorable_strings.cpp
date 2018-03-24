// 955B
#include <iostream>
#include <map>
using namespace std;

int main() {
  string s; cin >> s;
  map<char, int> letter_freqs;
  for (char c : s) {
    letter_freqs[c]++;
  }
  if (letter_freqs.size() == 4) {
    cout << "Yes\n";
    return 0;
  }
  if (letter_freqs.size() == 3) {
    for (const auto& kv : letter_freqs) {
      if (kv.second >= 2) {
        cout << "Yes\n";
        return 0;
      }
    }
  }
  if (letter_freqs.size() == 2) {
    auto it = letter_freqs.begin();
    int freq1 = it->second;
    it++;
    int freq2 = it->second;
    if (freq1 >= 2 && freq2 >= 2) {
      cout << "Yes\n";
      return 0;
    }
  }
  cout << "No\n";
}
