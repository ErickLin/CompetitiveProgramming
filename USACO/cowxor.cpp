/*
ID: Jugglebrosjr2
LANG: C++
TASK: cowxor
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    ifstream fin("cowxor.in");
    ofstream fout("cowxor.out");
    int n;
    fin >> n;
    int maxXor, start, end;
    map<int, int> prefixPos;
    //Tells whether the prefix of bits has been seen, and the least significant
    //position in which it was seen
    vector<int> bitsSeen(1 << 21);
    fill(bitsSeen.begin(), bitsSeen.end(), 21);
    int prev = 0;
    for (int i = 0; i < n; i++) {
        int a;
        fin >> a;
        if (a > maxXor) {
            maxXor = a;
            start = i;
            end = i;
        } 
        int newXor = prev ^ a;
        //cout << "New xor: " << newXor << '\n';
        if (i == 0) {
            maxXor = a;
            start = 0;
            end = 0;
        } else {
            int bestXor = 0;
            //try to get the opposite bit for each place, starting from the most
            //significant
            for (int pos = 20; pos >= 0; pos--) {
                int wantedBit = (newXor & (1 << pos)) ^ (1 << pos);
                /*
                cout << "Wanted bit: " << wantedBit << '\n';
                cout << "Try: " << (bestXor | wantedBit) << '\n';
                */
                if (bitsSeen[bestXor | wantedBit] <= pos) {
                    bestXor |= wantedBit;
                } else {
                    bestXor |= newXor & (1 << pos);
                }
                //cout << "So far: " << bestXor << '\n';
            }
            //cout << "Best xor: " << bestXor << '\n';
            if ((newXor ^ bestXor) > maxXor) {
                maxXor = newXor ^ bestXor;
                start = prefixPos[bestXor] + 1;
                end = i;
            }
        }
        int newBitsSeen = 0;
        for (int pos = 20; pos >= 0; pos--) {
            newBitsSeen |= newXor & (1 << pos);
            bitsSeen[newBitsSeen] = min(bitsSeen[newBitsSeen], pos);
        }
        prefixPos[newXor] = i;
        prev = newXor;
    }
    fout << maxXor << ' ' << start + 1 << ' ' << end + 1 << '\n';
    return 0;
}
