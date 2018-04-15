#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef vector<int> vi;

class JustBrackets {
 public:
   struct letter {
     char c;
     int imbalance;
     int max_ahead_imbalance;
   };

   string getSmallest(string s) {
     vector<letter> letters(s.size());
     int running_imbalance = 0;
     forf(i, s.size()) {
       if (s[i] == '(') {
         running_imbalance++;
       } else {
         running_imbalance--;
       }
       letters[i].imbalance = running_imbalance;
       letters[i].c = s[i];
     }
     int running_max_ahead_imbalance = 0;
     forb(i, letters.size()) {
       running_max_ahead_imbalance = max(running_max_ahead_imbalance, letters[i].imbalance);
       letters[i].max_ahead_imbalance = running_max_ahead_imbalance;
     }

     forf(i, letters.size() - 1) {
       if (letters[i].c == '(' && letters[i + 1].c == ')' && letters[i].imbalance < letters[i].max_ahead_imbalance) {
         letters.erase(letters.begin() + i + 1);
         letters.erase(letters.begin() + i);
         i--;
       }
     }

     string ret;
     forf(i, letters.size()) {
       ret += letters[i].c;
     }
     return ret;
   }
};
