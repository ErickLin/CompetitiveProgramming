#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    int p;
    cin >> p;
    while (p--) {
        int k, n;
        cin >> k >> n;
        int s1 = n * (n + 1) / 2;
        int s2 = n * n;
        int s3 = n * (n + 1);
        cout << k << " " << s1 << " " << s2 << " " << s3 << '\n';
    }
    return 0;
}
