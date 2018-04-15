#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef vector<int> vi;

class JustBrackets {
 public:
   void recurse(string cur, string& smallest, set<string>& visited) {
     visited.insert(cur);
     smallest = min(smallest, cur);
     forf(i, cur.size() - 2) {
       if (cur[i] == '(' && cur[i + 1] == ')') {
         string next;
         forf(j, cur.size()) {
           if (j != i && j != i + 1) {
             next += cur[j];
           }
         }
         if (!visited.count(next)) {
           recurse(next, smallest, visited);
         }
       }
     }
   }

   string getSmallest(string s) {
     string smallest = s;
     set<string> visited;
     recurse(s, smallest, visited);
     return smallest;
   }
};
