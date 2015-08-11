/*
ID: Jugglebrosjr2
LANG: C++
TASK: prime3
*/
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

typedef vector<vector<int> > square;
set<string> ans;

string toString(square &sq) {
    string ret = "";
    for (int i = 0; i < sq.size(); i++) {
        for (int j = 0; j < sq[0].size(); j++) {
            ostringstream ss;
            ss << sq[i][j];
            ret += ss.str();
        }
        ret += '\n';
    }
    return ret;
}

int getDigit(int num, int pos) {
    int dec = 10;
    for (int i = 0; i < pos; i++) {
        dec *= 10;
    }
    return num % dec / (dec / 10);
}

//last step of the recursion
//fills 2nd, 3rd, and 4th rows
void fillRow(square &sq, vector<bool> &isPrime, int a, int r) {
    int sumDigits = sq[r][1] + sq[r][2] + sq[r][3];
    for (int i = 0; i <= 9; i++) {
        int lastDigit = a - sumDigits - i;
        if (lastDigit >= 0 && lastDigit <= 9) {
            sq[r][0] = i;
            sq[r][4] = lastDigit;
            int num = 0;
            int dec = 1;
            for (int j = 0; j < 5; j++) {
                num += sq[r][4 - j] * dec;
                dec *= 10;
            }
            if (num >= 10000 && isPrime[num]) {
                if (r == 3) {
                    int num1 = 0, sumDigits1 = 0;
                    dec = 1;
                    for (int j = 0; j < 5; j++) {
                        num1 += sq[4 - j][0] * dec;
                        dec *= 10;
                        sumDigits1 += sq[4 - j][0];
                    }
                    int num2 = 0, sumDigits2 = 0;
                    dec = 1;
                    for (int j = 0; j < 5; j++) {
                        num2 += sq[4 - j][4] * dec;
                        dec *= 10;
                        sumDigits2 += sq[4 - j][4];
                    }
                    if (num1 >= 10000 && isPrime[num1] && sumDigits1 == a
                            && num2 >= 10000 && isPrime[num2] && sumDigits2 == a) {
                        ans.insert(toString(sq));
                    }
                } else {
                    fillRow(sq, isPrime, a, r + 1);
                }
            }
            sq[r][0] = 0;
            sq[r][4] = 0;
        }
    }
}

//fills the 3rd column
void fill5(square &sq, vector<bool> &isPrime, int a) {
    int sumDigits = sq[0][2] + sq[2][2] + sq[4][2];
    for (int i = 0; i <= 9; i++) {
        int lastDigit = a - sumDigits - i;
        if (lastDigit >= 0 && lastDigit <= 9) {
            sq[1][2] = i;
            sq[3][2] = lastDigit;
            int num = 0;
            int dec = 1;
            for (int j = 0; j < 5; j++) {
                num += sq[4 - j][2] * dec;
                dec *= 10;
            }
            if (num >= 10000 && isPrime[num]) {
                fillRow(sq, isPrime, a, 1);
            }
            sq[1][2] = 0;
            sq[3][2] = 0;
        }
    }
}

//both diagonals and first row already filled
//fills the 2nd and 4th columns, as well as the 5th row 
void fill4(square &sq, vector<bool> &isPrime, int a) {
    //start filling the 2nd column
    int sumDigits = sq[0][1] + sq[1][1] + sq[3][1];
    for (int i = 0; i <= 9; i++) {
        int lastDigit = a - sumDigits - i;
        if (lastDigit >= 0 && lastDigit <= 9) {
            sq[2][1] = i;
            sq[4][1] = lastDigit;
            int s = 0;
            //num holds the value of the 2nd column
            int num = 0;
            int dec = 1;
            for (int j = 0; j < 5; j++) {
                num += sq[4 - j][1] * dec;
                dec *= 10;
            }
            if (num >= 10000 && isPrime[num]) {
                int sumDigits2 = sq[0][3] + sq[1][3] + sq[3][3];
                for (int k = 0; k <= 9; k++) {
                    lastDigit = a - sumDigits2 - k;
                    if (lastDigit >= 0 && lastDigit <= 9) {
                        sq[2][3] = k;
                        sq[4][3] = lastDigit;
                        num = 0;
                        dec = 1;
                        for (int j = 0; j < 5; j++) {
                            num += sq[4 - j][3] * dec;
                            dec *= 10;
                        }
                        if (num >= 10000 && isPrime[num]) {
                            int sumDigits3 = sq[4][0] + sq[4][1] + sq[4][3] + sq[4][4];
                            //fill in the middle digit of last row
                            lastDigit = a - sumDigits3;
                            if (lastDigit >= 0 && lastDigit <= 9) {
                                sq[4][2] = lastDigit;
                                num = 0;
                                dec = 1;
                                for (int j = 0; j < 5; j++) {
                                    num += sq[4][4 - j] * dec;
                                    dec *= 10;
                                }
                                if (num >= 10000 && isPrime[num]) {
                                    fill5(sq, isPrime, a);
                                }
                                sq[4][2] = 0;
                            }
                        }
                        sq[2][3] = 0;
                        sq[4][3] = 0;
                    }
                }
            }
            sq[2][1] = 0;
            sq[4][1] = 0;
        }
    }
}

//both diagonals already filled
void fillRow1(square &sq, vector<int> &validPrimes, vector<bool> &isPrime, int a) {
    for (int i = 0; i < validPrimes.size(); i++) {
        if (getDigit(validPrimes[i], 4) == sq[0][0]
                && getDigit(validPrimes[i], 0) == sq[0][4]) {
            for (int j = 1; j < 4; j++) {
                sq[0][j] = getDigit(validPrimes[i], 4 - j);
            }
            fill4(sq, isPrime, a);
            for (int j = 1; j < 4; j++) {
                sq[0][j] = 0;
            }
        }
    }
}

//first diagonal already filled
void fillDiag2(square &sq, vector<int> &validPrimes, vector<bool> &isPrime, int a) {
    for (int i = 0; i < validPrimes.size(); i++) {
        //most significant digit must be even because it is least significant
        //digit of first column
        if (getDigit(validPrimes[i], 4) % 2 == 1
                && getDigit(validPrimes[i], 2) == sq[2][2]) {
            for (int j = 0; j < 5; j++) {
                sq[4 - j][j] = getDigit(validPrimes[i], 4 - j);
            }
            fillRow1(sq, validPrimes, isPrime, a);
            for (int j = 0; j < 5; j++) {
                if (j != 2) {
                    sq[4 - j][j] = 0;
                }
            }
        }
    }
}

void fillDiag1(vector<int> &validFirst, vector<int> &validPrimes
        , vector<bool> &isPrime, int a) {
    for (int i = 0; i < validFirst.size(); i++) {
        square sq(5, vector<int>(5));
        for (int j = 0; j < 5; j++) {
            sq[j][j] = getDigit(validFirst[i], 4 - j);
        }
        fillDiag2(sq, validPrimes, isPrime, a);
        for (int j = 0; j < 5; j++) {
            sq[j][j] = 0;
        }
    }
}
        
int main() {
    ifstream fin("prime3.in");
    ofstream fout("prime3.out");
    int a, b;
    fin >> a >> b;
    vector<bool> isPrime(100000);
    for (int i = 2; i < 100000; i++) {
        isPrime[i] = true;
    }
    for (int i = 2; i <= (int) sqrt(100000); i++) {
        for (int j = i * i; j < 100000; j += i) {
            isPrime[j] = false;
        }
    }
    vector<int> validPrimes;
    vector<int> validFirst;
    for (int i = 10000; i < 100000; i++) {
        if (isPrime[i]) {
            int firstDigit = getDigit(i, 4);
            int sumDigits = 0;
            for (int pos = 0; pos < 5; pos++) {
                sumDigits += getDigit(i, pos);
            }
            if (sumDigits == a) {
                validPrimes.push_back(i);
                if (firstDigit == b) {
                    validFirst.push_back(i);
                }
            }
        }
    }
    fillDiag1(validFirst, validPrimes, isPrime, a);
    set<string>::iterator it = ans.begin();
    fout << *it;
    it++;
    while (it != ans.end()) {
        fout << '\n' << *it;
        it++;
    }
    return 0;
}
