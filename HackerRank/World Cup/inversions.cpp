#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int countInversions(vector<int> &arr) {
    if (arr.size() >= 2) {
        vector<int> left(arr.size() >> 1);
        for (int i = 0; i < (arr.size() >> 1); i++) {
            left[i] = arr[i];
        }
        vector<int> right(arr.size() - (arr.size() >> 1));
        for (int i = (arr.size() >> 1); i < arr.size(); i++) {
            right[i - (arr.size() >> 1)] = arr[i];
        }
        int inversions = countInversions(left) + countInversions(right);
        int i = 0;
        int j = 0;
        while (i + j < arr.size()) {
            if (j == right.size() || (i < left.size() && left[i] <= right[j])) {
                arr[i + j] = left[i++];
            } else {
                arr[i + j] = right[j++];
                inversions += left.size() - i;
            }
        }
        return inversions;
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> aTemp(a);
    int best = countInversions(aTemp);
    int bestI = -1, bestJ = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            aTemp = a;
            int temp = aTemp[i];
            aTemp[i] = aTemp[j];
            aTemp[j] = temp;
            int numInv = countInversions(aTemp);
            if (numInv < best) {
                best = numInv;
                bestI = i;
                bestJ = j;
            }
        }
    }
    if (bestI == -1) {
        cout << "Cool Array\n";
    } else {
        cout << bestI + 1 << ' ' << bestJ + 1 << '\n';
    }
    return 0;
}
