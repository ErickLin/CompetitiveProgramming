/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: gravity
*/
import java.io.*;
import java.util.*;

class gravity
{
    static boolean[][] blocked;
    static int[][][] dp;
    static int rows, cols, yD, xD, best;
    static final int MAX = 99999999;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("gravity.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("gravity.out")));
        StringTokenizer rc = new StringTokenizer(in.readLine());
        rows = Integer.parseInt(rc.nextToken());
        cols = Integer.parseInt(rc.nextToken());
        blocked = new boolean[rows][cols];
        //positions of C and D
        int yC = 0, xC = 0;
        for (int i = 0; i < rows; i++)
        {
            String line = in.readLine();
            for (int j = 0; j < cols; j++)
            {
                if (line.substring(j, j + 1).equals("#"))
                    blocked[i][j] = true;
                else
                {
                    blocked[i][j] = false;
                    if (line.substring(j, j + 1).equals("C"))
                    {
                        //position of C
                        yC = i;
                        xC = j;
                    }
                    if (line.substring(j, j + 1).equals("D"))
                    {
                        //position of D
                        yD = i;
                        xD = j;
                    }
                }
            }
        }
        in.close();
        //the value of gravity
        //int g = 1;
        //int flips = 0;
        //direction (right or left)
        //int dx = Integer.signum(xD - xC);
        dp = new int[rows][cols][3];
        best = MAX;
        boolean[][][] visited = new boolean[rows][cols][3];
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                for (int k = 0; k < 3; k++)
                {
                    dp[i][j][k] = 0;
                    visited[i][j][k] = false;
                }
        visited[yC][xC][2] = true;
        visited[yC][xC][0] = true;
        findBest(yC, xC, 1, 0, visited);
        findBest(yC, xC, -1, 1, visited);
        if (best < MAX)
            out.println(best);
        else
            out.println("-1");
        out.close();
        System.exit(0);
    }
    
    public static int findBest(int yC, int xC, int g, int flips, boolean[][][] visited)
    {
        //System.out.println(yC + " " + xC + " " + g + " " + flips);
        int yTemp = yC;
        if (dp[yC][xC][g + 1] != 0)
            return dp[yC][xC][g + 1];
        if (!valid(yC, xC, g))
        {
            //System.out.println(yC + " " + xC);
            dp[yC][xC][g + 1] = MAX;
            return MAX;
        }
        yC = fall(yC, xC, g);
        if (yC == yD && xC == xD)
        {
            dp[yC][xC][g + 1] = flips;
            dp[yTemp][xC][g + 1] = flips;
            if (flips < best)
                best = flips;
            return flips;
        }
        int a = MAX, b = MAX, c = MAX;
        if (xC + 1 < cols && !visited[yC][xC + 1][g + 1])
        {
            visited[yC][xC + 1][g + 1] = true;
            a = findBest(yC, xC + 1, g, flips, visited);
            visited[yC][xC + 1][g + 1] = false;
        }
        if (xC - 1 >= 0 && !visited[yC][xC - 1][g + 1])
        {
            visited[yC][xC - 1][g + 1] = true;
            b = findBest(yC, xC - 1, g, flips, visited);
            visited[yC][xC - 1][g + 1] = false;
        }
        /*if (xC + 1 < cols && !visited[yC][xC + 1][-g + 1])
            c = findBest(yC, xC + 1, -g, flips + 1, visited);
        if (xC - 1 >= 0 && !visited[yC][xC - 1][-g + 1])
            d = findBest(yC, xC - 1, -g, flips + 1, visited);*/
        if (!visited[yC][xC][-g + 1])
        {
            visited[yC][xC][-g + 1] = true;
            c = findBest(yC, xC, -g, flips + 1, visited);
            visited[yC][xC][-g + 1] = false;
        }
        dp[yC][xC][g + 1] = Math.min(a, Math.min(b, c));
        dp[yTemp][xC][g + 1] = dp[yC][xC][g + 1];
        return dp[yC][xC][g + 1];
    }
    
    //fall onto the nearest ground below
    public static int fall(int y, int x, int g)
    {
        for (int h = y; h + g >= 0 && h + g < rows; h += g)
            if (blocked[h + g][x] || (h == yD && x == xD))
                return h;
        return -1;
    }
    
    public static boolean valid(int y, int x, int g)
    {
        if (blocked[y][x])
            return false;
        /*boolean rightSide = true;
        if (x == xD)
        {
            rightSide = false;
            //search the opposite vertical direction to see if D is reachable by flipping
            for (int h = y; h + g >= 0 && h + g < rows; h -= g)
                if (h == yD)
                    rightSide = true;
        }*/
        for (int h = y; h + g >= 0 && h + g < rows; h += g)
        {
            //System.out.println(g + " (" + h + ", " + x + ")");
            /*if (h == yD)
                rightSide = true;*/
            if (blocked[h + g][x] || (h == yD && x == xD))
                return true;
        }
        return false;
    }
}