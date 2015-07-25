/*
ID: Jugglebrosjr2
LANG: C++
TASK: checker
 */
#include <cstdlib>
#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N, numSols;
vector<int> colOrder, mirOrder;
//vector<bool> colMarked, diag1Marked, diag2Marked;
int colMarked, diag1Marked, diag2Marked;
vector< vector<int> > solutions;

void iterate(vector<int> colOrder, int row, int colsThisRow)
{
    if (row == N)
    {
        solutions.push_back(colOrder);
        numSols++;
        if (N % 2 == 0 || colOrder[0] != N/2)
        {
            solutions.push_back(mirOrder);
            numSols++;
        }
    }
    else
    {
        for (int col = 0; col < colsThisRow; col++)
        {
            //if (!colMarked[col] && !diag1Marked[col + row] && !diag2Marked[col - row + N - 1])
            if (((colMarked & (1 << col)) == 0) && ((diag1Marked & (1 << (col + row))) == 0) && ((diag2Marked & (1 << (col - row + N - 1))) == 0))
            {
                colOrder[row] = col;
                if (N % 2 == 0 || row != 0 || col != N/2)
                    mirOrder[row] = N - 1 - col;
                /*colMarked[col] = true;
                diag1Marked[col + row] = true;
                diag2Marked[col - row + N - 1] = true;*/
                colMarked |= 1 << col;
                diag1Marked |= 1 << (col + row);
                diag2Marked |= 1 << (col - row + N - 1);
                iterate(colOrder, row + 1, N);
                /*colMarked[col] = false;
                diag1Marked[col + row] = false;
                diag2Marked[col - row + N - 1] = false;*/
                colMarked &= ~(1 << col);
                diag1Marked &= ~(1 << (col + row));
                diag2Marked &= ~(1 << (col - row + N - 1));
            }
        }
    }
}

int main(int argc, char** argv)
{
    ifstream fin("checker.in");
    ofstream fout("checker.out");
    fin >> N;
    numSols = 0;
    colOrder.resize(N);
    mirOrder.resize(N);
    /*colMarked.resize(N);
    diag1Marked.resize(2 * N - 1);
    diag2Marked.resize(2 * N - 1);*/
    //consider only the left half of the board on 1st row
    //(symmetry takes care of half of solutions)
    int colsFirstRow;
    if (N % 2 == 0)
        colsFirstRow = N / 2;
    else
        colsFirstRow = N / 2 + 1;
    iterate(colOrder, 0, colsFirstRow);
    sort(solutions.begin(), solutions.end());
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < solutions[i].size(); j++)
        {
            fout << solutions[i][j] + 1;
            if (j < solutions[i].size() - 1)
                fout << " ";
        }
        fout << "\n";
    }
    fout << numSols << "\n";
    return 0;
}