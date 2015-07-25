#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    int sideLen;
    cin >> sideLen;
    vector<vector<int> > spiral(sideLen + 1, vector<int>(sideLen + 1));
    spiral[sideLen >> 1][sideLen >> 1] = 1;
    int count = 1;
    int i = (sideLen >> 1);
    int j = (sideLen >> 1);
    for (int len = 1; len < sideLen; len++) {
        for (int k = 0; k < len; k++) {
            count++;
            j += (len % 2 == 1 ? 1 : -1);
            spiral[i][j] = count;
        }
        for (int k = 0; k < len; k++) {
            count++;
            i += (len % 2 == 1 ? 1 : -1);
            spiral[i][j] = count;
        }
    }
    for (int k = 0; k < sideLen; k++) {
        count++;
        j++;
        spiral[i][j] = count;
    }
    int sum = 0;
    for (int a = 0; a < sideLen; a++) {
        sum += spiral[a][a];
        sum += spiral[a][sideLen - a - 1];
    }
    sum -= spiral[sideLen >> 1][sideLen >> 1];
    cout << sum << '\n';
}
