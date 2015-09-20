#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        int a, b, c;
        cin >> n >> a >> b >> c;
        int sum = a + b + c;
        long long left = 1, right = n;
        long long cost = 0;
        while (left != right) {
            if (left + 1 == right) {
                if (a > b) {
                    cost += a;
                    right--;
                } else {
                    cost += b;
                    left++;
                }
            } else {
                long long m = right - left + 1;
                long long sizeA, sizeB, sizeC;
                if (min(min(a, b), c) == a) {
                    sizeB = m * sum / (9 * b);
                    sizeC = m * sum / (9 * c);
                    sizeA = m - sizeB - sizeC;
                    if (sizeA < 0) {
                        if (sizeB > sizeC) {
                            sizeB += sizeA;
                        } else {
                            sizeC += sizeA;
                        }
                        sizeA = 0;
                    }
                } else if (min(min(a, b), c) == b) {
                    sizeA = m * sum / (9 * a);
                    sizeC = m * sum / (9 * c);
                    sizeB = m - sizeA - sizeC;
                    if (sizeB < 0) {
                        if (sizeA > sizeC) {
                            sizeA += sizeB;
                        } else {
                            sizeC += sizeB;
                        }
                        sizeB = 0;
                    }
                } else {
                    sizeA = m * sum / (9 * a);
                    sizeB = m * sum / (9 * b);
                    sizeC = m - sizeA - sizeB;
                    if (sizeC < 0) {
                        if (sizeA > sizeB) {
                            sizeA += sizeC;
                        } else {
                            sizeB += sizeC;
                        }
                        sizeC = 0;
                    }
                }
                if (sizeA >= 2 && sizeB == 0 && sizeC == 0) {
                    if (b <= c) {
                        sizeB = 1;
                    } else {
                        sizeC = 1;
                    }
                    sizeA--;
                }
                if (sizeA == 0 && sizeB >= 2 && sizeC == 0) {
                    if (a <= c) {
                        sizeA = 1;
                    } else {
                        sizeC = 1;
                    }
                    sizeB--;
                }
                if (sizeA == 0 && sizeB == 0 && sizeC >= 2) {
                    if (a < b) {
                        sizeA = 1;
                    } else {
                        sizeB = 1;
                    }
                    sizeC--;
                }
                int exprA = (sizeA > 0) ? a : 0;
                int exprB = (sizeB > 0) ? b : 0;
                int exprC = (sizeC > 0) ? c : 0;
                if (max(max(exprA, exprB), exprC) == exprA) {
                    cost += a;
                    right = left + sizeA - 1;
                } else if (max(max(exprA, exprB), exprC) == exprB) {
                    cost += b;
                    left += sizeA;
                    right = left + sizeB - 1;
                } else {
                    cost += c;
                    left = right - sizeC + 1;
                }
                //cout << sizeA << ' ' << sizeB << ' ' << sizeC << '\n';
                //cout << left << ' ' << right << '\n';
            }
        }
        cout << cost << '\n';
    }
    return 0;
}
