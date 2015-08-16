#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    double mean = (double) sum / n;

    sort(a.begin(), a.end());
    double median;
    if (n % 2) {
        median = a[n >> 1];
    } else {
        median = ((double) a[n >> 1] + a[(n >> 1) - 1]) / 2;
    }

    int mode = a[0];
    int maxStreak = 1;
    int streak = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            streak++;
            if (streak > maxStreak) {
                maxStreak = streak;
                mode = a[i];
            }
        } else {
            streak = 1;
        }
    }

    double sumSquareDiff = 0;
    for (int i = 0; i < n; i++) {
        sumSquareDiff += (a[i] - mean) * (a[i] - mean);
    }
    double stdDev = sqrt(sumSquareDiff / n);
    
    double stdErr = stdDev / sqrt(n);
    double low = mean - 1.96 * stdErr;
    double high = mean + 1.96 * stdErr;
    cout << fixed << setprecision(1) << mean << '\n' << median << '\n' << mode << '\n' << stdDev << '\n'
            << low << ' ' << high << '\n';
    return 0;
}