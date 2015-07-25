/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: clocks
*/
import java.io.*;
import java.util.*;

class clocks
{
    static final int movesClock[][] = new int[][]{
            {3,3,3,3,3,2,3,2,0},
            {2,3,2,3,2,3,1,0,1},
            {3,3,3,2,3,3,0,2,3},
            {2,3,1,3,2,0,2,3,1},
            {2,3,2,3,1,3,2,3,2},
            {1,3,2,0,2,3,1,3,2},
            {3,2,0,3,3,2,3,3,3},
            {1,0,1,3,2,3,2,3,2},
            {0,2,3,2,3,3,3,3,3}};
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("clocks.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("clocks.out")));
        int[] numOfMoves = new int[9];
        for (int i = 0; i < 9; i += 3)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int clockNum = i; clockNum < i + 3; clockNum++)
            {
                int time = Integer.parseInt(line.nextToken());
                int movesNeeded = 4 - time / 3;
                for (int moveNum = 0; moveNum < 9; moveNum++)
                    numOfMoves[moveNum] = (numOfMoves[moveNum] + movesNeeded * movesClock[clockNum][moveNum]) % 4;
            }
        }
        in.close();
        String ans = "";
        for (int moveNum = 0; moveNum < 9; moveNum++)
            for (int num = 0; num < numOfMoves[moveNum]; num++)
                ans += (moveNum + 1) + " ";
        ans = ans.trim();
        out.println(ans);
        out.close();
        System.exit(0);
    }
}