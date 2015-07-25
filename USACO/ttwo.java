/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: ttwo
*/
import java.io.*;
import java.util.*;

class ttwo
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("ttwo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ttwo.out")));
        //initial positions and velocities of cows and Farmer John
        int cCi = 0, rCi = 0, dcC = 0, drC = -1, cFi = 0, rFi = 0, dcF = 0, drF = -1;
        boolean[][] blocked = new boolean[10][10];
        String line;
        for (int r = 0; r < 10; r++)
        {
            line = in.readLine();
            for (int c = 0; c < 10; c++)
            {
                if (line.substring(c, c + 1).equals("*"))
                    blocked[r][c] = true;
                if (line.substring(c, c + 1).equals("C"))
                {
                    rCi = r;
                    cCi = c;
                }
                if (line.substring(c, c + 1).equals("F"))
                {
                    rFi = r;
                    cFi = c;
                }
            }
        }
        in.close();
        /*for (int r = 0; r < 10; r++)
        {
            for (int c = 0; c < 10; c++)
            {
                if (blocked[r][c])
                    System.out.print("*");
                else if (r == rCi && c == cCi)
                    System.out.print("C");
                else if (r == rFi && c == cFi)
                    System.out.print("F");
                else
                    System.out.print(".");
            }
            System.out.println();
        }*/
        int cC = cCi, rC = rCi, cF = cFi, rF = rFi;
        for (int t = 0; t <= 400 * 400; t++)
        {
            if (rC == rF && cC == cF)
            {
                out.println(t);
                out.close();
                System.exit(0);
            }
            if (rC + drC < 0 || rC + drC > 9 || cC + dcC < 0 || cC + dcC > 9 || blocked[rC + drC][cC + dcC])
            {
                //rotate
                //if facing north
                if (drC == -1)
                {
                    drC = 0;
                    dcC = 1;
                }
                //if facing east
                else if (dcC == 1)
                {
                    drC = 1;
                    dcC = 0;
                }
                //if facing south
                else if (drC == 1)
                {
                    drC = 0;
                    dcC = -1;
                }
                //if facing west
                else
                {
                    drC = -1;
                    dcC = 0;
                }
            }
            else
            {
                rC += drC;
                cC += dcC;
            }
            if (rF + drF < 0 || rF + drF > 9 || cF + dcF < 0 || cF + dcF > 9 || blocked[rF + drF][cF + dcF])
            {
                //rotate
                //if facing north
                if (drF == -1)
                {
                    drF = 0;
                    dcF = 1;
                }
                //if facing east
                else if (dcF == 1)
                {
                    drF = 1;
                    dcF = 0;
                }
                //if facing south
                else if (drF == 1)
                {
                    drF = 0;
                    dcF = -1;
                }
                //if facing west
                else
                {
                    drF = -1;
                    dcF = 0;
                }
            }
            else
            {
                rF += drF;
                cF += dcF;
            }
            //if back at start position
            if (rC == rCi && cC == cCi && drC == -1 && rF == rFi && cF == cFi && drF == -1)
            {
                out.println("0");
                out.close();
                System.exit(0);
            }
        }
        out.println("0");
        out.close();
        System.exit(0);
    }
}