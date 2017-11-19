// 515C
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int cmp(char a, char b) {
    return a > b;
}

int main() {
    vector<char> list;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char dig;
        cin >> dig;
        if (dig == '4') {
            list.push_back('3');
            list.push_back('2');
            list.push_back('2');
        } else if (dig == '6') {
            list.push_back('5');
            list.push_back('3');
        } else if (dig == '8') {
            list.push_back('7');
            for (int j = 0; j < 3; j++) {
                list.push_back('2');
            }
        } else if (dig == '9') {
            list.push_back('7');
            list.push_back('2');
            list.push_back('3');
            list.push_back('3');
        } else if (dig != '0' && dig != '1') {
            list.push_back(dig);
        }
    }
    sort(list.begin(), list.end(), cmp);
    for (int i = 0; i < list.size(); i++) {
        cout << list[i];
    }
    cout << '\n';
    return 0;
}
