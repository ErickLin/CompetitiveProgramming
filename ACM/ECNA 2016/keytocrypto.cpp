#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;

int main() {
  string ciphertext, secret_word;
  cin >> ciphertext >> secret_word;
  string orig_msg;
  forf(i, ciphertext.size()) {
    if (i < secret_word.size()) {
      orig_msg.push_back(ciphertext[i] - (secret_word[i] - 'A'));
    } else {
      orig_msg.push_back(ciphertext[i] - (orig_msg[i - secret_word.size()] - 'A'));
    }
    if (orig_msg[i] < 'A') {
      orig_msg[i] += 26;
    }
  }
  cout << orig_msg << '\n';
  return 0;
}
