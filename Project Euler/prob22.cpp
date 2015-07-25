#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<string> names;
  string s;
  while (getline(cin, s, ',')) {
    names.push_back(s);
  }
  sort(names.begin(), names.end());
  long long totalScore = 0;
  for (int i = 0; i < names.size(); i++) {
    long long score = 0;
    for (int j = 1; j < names[i].size() - 1; j++) {
      score += names[i].at(j) - 'A' + 1;
    }
    totalScore += (i + 1) * score;
  }
  cout << totalScore << '\n';
}
