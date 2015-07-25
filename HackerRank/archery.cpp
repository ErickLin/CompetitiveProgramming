#include <cstdlib>
#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv) {
    int n, m;
    vector<int> r, x1, y1, x2, y2;
    string input;
    
    getline(cin, input);
    stringstream stream(input);
    stream >> n;
    
    getline(cin, input);
    istringstream stream8(input);
    int num;
    while (stream8 >> num) {
        r.push_back(num);
    }
    
    getline(cin, input);
    stringstream stream2(input);
    stream2 >> m;
    
    r.resize(n);
    x1.resize(m);
    y1.resize(m);
    x2.resize(m);
    y2.resize(m);
    
    getline(cin, input);
    istringstream stream3(input);
    while (stream3 >> num) {
        x1.push_back(num);
    }

    getline(cin, input);
    istringstream stream4(input);
    while (stream4 >> num) {
        y1.push_back(num);
    }

    getline(cin, input);
    istringstream stream5(input);
    while (stream5 >> num) {
        x2.push_back(num);
    }

    getline(cin, input);
    istringstream stream6(input);
    while (stream6 >> num) {
        y2.push_back(num);
    }
    
    sort(r.begin(), r.end());
    //Prefix sum that keeps track of current number of circles
    int circleNum = 0;
    //Keeps track of number of circles within current radius equal to index
    vector<int> prefix;
    prefix.resize(n);
    //Loop through all integer radii
    for (int i = 1; i <= r[n - 1]; i++) {
        //If current radius = radius of current circle
        if (r[circleNum] == i) {
            circleNum++;
        }
        prefix[i] = circleNum;
    }
    for (int i = r[n - 1] + 1; i <= 1000000; i++) {
        prefix[i] = circleNum;
    }
    long count = 0;
    for (int i = 0; i < m; i++) {
        long r1t = x1[i] * x1[i] + y1[i] * y1[i];
        long r2t = x2[i] * x2[i] + y2[i] * y2[i];
        int r1, r2;
        if (r1t > r2t) {
            r1 = (int) floor(sqrt(r1t));
            r2 = (int) ceil(sqrt(r2t));
            count += prefix[r1] - prefix[r2 - 1];
        } else if (r2t > r1t) {
            r1 = (int) ceil(sqrt(r1t));
            r2 = (int) floor(sqrt(r2t));
            count += prefix[r2] - prefix[r1 - 1];
        }
    }
    cout << count;
    return 0;
}