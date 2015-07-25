/*
ID: Jugglebrosjr2
LANG: C++
TASK: shuttle
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

int main() {
  ifstream fin("shuttle.in");
  ofstream fout("shuttle.out");
  int n;
  fin >> n;
  vector<char> start((n << 1) + 1);
  vector<char> end((n << 1) + 1);
  for (int i = 0; i < n; i++) {
    start[i] = 'W';
    end[i] = 'B';
  }
  start[n] = ' ';
  end[n] = ' ';
  for (int i = n + 1; i <= (n << 1); i++) {
    start[i] = 'B';
    end[i] = 'W';
  }
  queue<pair<vector<char>, vector<int> > > states;
  vector<int> movesEmpty;
  states.push(make_pair(start, movesEmpty));
  set<vector<char> > visited;
  visited.insert(start);
  while (!states.empty()) {
    vector<char> state = states.front().first;
    vector<int> moves = states.front().second;
    states.pop();
    if (state == end) {
      for (int i = 0; i < moves.size(); i++) {
        fout << (moves[i] + 1);
        if (i == moves.size() - 1 || i % 20 == 19) {
          fout << '\n';
        } else {
          fout << ' ';
        }
      }
      return 0;
    }
    int spaceInd = -1;
    for (int i = 0; i < state.size(); i++) {
      if (state[i] == ' ') {
        spaceInd = i;
      }
    }
    if (spaceInd - 2 >= 0 && state[spaceInd - 2] == 'W' && state[spaceInd - 1] == 'B') {
      vector<char> newState = state;
      vector<int> newMoves = moves;
      newState[spaceInd - 2] = ' ';
      newState[spaceInd] = 'W';
      if (visited.find(newState) == visited.end()) {
        newMoves.push_back(spaceInd - 2);
        states.push(make_pair(newState, newMoves));
        visited.insert(newState);
      }
    }
    if (spaceInd - 1 >= 0 && state[spaceInd - 1] == 'W') {
      vector<char> newState = state;
      vector<int> newMoves = moves;
      newState[spaceInd - 1] = ' ';
      newState[spaceInd] = 'W';
      if (visited.find(newState) == visited.end()) {
      newMoves.push_back(spaceInd - 1);
      states.push(make_pair(newState, newMoves));
      visited.insert(newState);
      }
    }
    if (spaceInd + 1 < state.size() && state[spaceInd + 1] == 'B') {
      vector<char> newState = state;
      vector<int> newMoves = moves;
      newState[spaceInd + 1] = ' ';
      newState[spaceInd] = 'B';
      if (visited.find(newState) == visited.end()) {
      newMoves.push_back(spaceInd + 1);
      states.push(make_pair(newState, newMoves));
      visited.insert(newState);
      }
    }
    if (spaceInd + 2 < state.size() && state[spaceInd + 2] == 'B' && state[spaceInd + 1] == 'W') {
      vector<char> newState = state;
      vector<int> newMoves = moves;
      newState[spaceInd + 2] = ' ';
      newState[spaceInd] = 'B';
      if (visited.find(newState) == visited.end()) {
      newMoves.push_back(spaceInd + 2);
      states.push(make_pair(newState, newMoves));
      visited.insert(newState);
      }
    }
  }
  return 0;
}
