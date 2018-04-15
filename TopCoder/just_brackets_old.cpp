#include <iostream>
#include <stack>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

class JustBrackets {
 public:
   string getSmallest(string s) {
     forf(i, s.size() - 1) {
       stack<int> possible;
       int j;
       for (j = i; j < s.size() - 1 && s[j] == '(' && s[j + 1] == ')'; j += 2) {
         possible.push(j);
       }
       if (j == s.size() || s[j] == '(') {
         while (!possible.empty()) {
           int pos = possible.top();
           possible.pop();
           s.erase(pos, 2);
         }
       } else {
         // skip past the entire just-analyzed substring
         i = j;
       }
     }
     return s;
   }
};
