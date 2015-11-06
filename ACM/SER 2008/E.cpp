#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = INT_MAX;
    while (n) {
        int t1, t2, t3;
        cin >> n >> t1 >> t2 >> t3;
        if (n) {
            //stage 1
            int numTicks = (n << 1);
            numTicks += n - 1;
            //stage 2
            numTicks += n;
            /*
            if (t2 < t1) {
                numTicks += t1 - t2;
            } else if (t2 > t1) {
                numTicks += n + t1 - t2;
            }
            */
            if (t2 > t1) {
                numTicks += t2 - t1;
            } else if (t2 < t1) {
                numTicks += n + t2 - t1;
            }
            //stage 3
            /*
            if (t3 > t2) {
                numTicks += t3 - t2;
            } else if (t3 < t2) {
                numTicks += n + t3 - t2;
            }
            */
            if (t3 < t2) {
                numTicks += t2 - t3;
            } else if (t3 > t2) {
                numTicks += n + t2 - t3;
            }
            cout << numTicks << '\n';
        }
    }
    return 0;
}
