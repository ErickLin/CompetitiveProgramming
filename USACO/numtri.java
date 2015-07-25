/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: numtri
*/
import java.io.*;
import java.util.*;

class numtri
{
    static int totalRows, tri[][], dp[][];
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("numtri.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("numtri.out")));
        totalRows = Integer.parseInt(in.readLine());
        tri = new int[totalRows][totalRows];
        dp = new int[totalRows][totalRows];
        for (int i = 0; i < totalRows; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int j = 0; line.hasMoreTokens(); j++)
            {
                tri[i][j] = Integer.parseInt(line.nextToken());
                dp[i][j] = -1;
            }
        }
        in.close();
        /*for (int i = 0; i < totalRows; i++)
        {
            for (int j = 0; j <= i; j++)
                System.out.print(tri[i][j] + " ");
            System.out.println();
        }*/
        out.println(sum(0, 0));
        out.close();
        System.exit(0);
    }
    
    public static int sum(int row, int col)
    {
        if (dp[row][col] > -1)
            return dp[row][col];
        else if (row < totalRows - 1)
            return dp[row][col] = tri[row][col] + Math.max(sum(row + 1, col), sum(row + 1, col + 1));
        else
            return tri[row][col];
    }
}