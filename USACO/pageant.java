/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: pageant
*/
import java.io.*;
import java.util.*;

class pageant
{
    static int n, m;
    static String[][] grid;
    static int[][] labeledGrid;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("pageant.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("pageant.out")));
        StringTokenizer firstLine = new StringTokenizer(in.readLine());
        n = Integer.parseInt(firstLine.nextToken());
        m = Integer.parseInt(firstLine.nextToken());
        grid = new String[n][m];
        for (int row = 0; row < n; row++)
        {
            String line = in.readLine();
            for (int column = 0; column < m; column++)
                grid[row][column] = line.substring(column, column + 1);
        }
        in.close();
        int spotNum = 1;
        labeledGrid = new int[n][m];
        for (int row = 0; row < n; row++)
            for (int column = 0; column < m; column++)
                if (grid[row][column].equals("X") && labeledGrid[row][column] == 0)
                {
                    label(row, column, spotNum);
                    spotNum++;
                }
        int minDist1 = m + n;
        int minDist2 = m + n;
        int minDist3 = m + n;
        for (int r1 = 0; r1 < n; r1++)
        for (int c1 = 0; c1 < m; c1++)
        for (int r2 = 0; r2 < n; r2++)
        for (int c2 = 0; c2 < m; c2++)
            if (r1 != r2 || c1 != c2)
                if (labeledGrid[r1][c1] != 0 && labeledGrid[r2][c2] != 0 && labeledGrid[r1][c1] != labeledGrid[r2][c2])
                {
                    int dist = abs(r1 - r2) + abs(c1 - c2);
                    if (labeledGrid[r1][c1] == 1 && labeledGrid[r2][c2] == 2 && dist < minDist1)
                        minDist1 = abs(r1 - r2) + abs(c1 - c2);
                    if (labeledGrid[r1][c1] == 1 && labeledGrid[r2][c2] == 3 && dist < minDist2)
                        minDist2 = abs(r1 - r2) + abs(c1 - c2);
                    if (labeledGrid[r1][c1] == 2 && labeledGrid[r2][c2] == 3 && dist < minDist3)
                        minDist3 = abs(r1 - r2) + abs(c1 - c2);
                }
        out.println(minDist1 + minDist2 + minDist3 - Math.max(Math.max(minDist1, minDist2), minDist3)- 2);
        out.close();
        System.exit(0);
    }
    
    public static void label(int row, int column, int value)
    {
        labeledGrid[row][column] = value;
        if (row > 0 && labeledGrid[row - 1][column] == 0 && grid[row - 1][column].equals("X"))
            label(row - 1, column, value);
        if (row < n - 1 && labeledGrid[row + 1][column] == 0 && grid[row + 1][column].equals("X"))
            label(row + 1, column, value);
        if (column > 0 && labeledGrid[row][column - 1] == 0 && grid[row][column - 1].equals("X"))
            label(row, column - 1, value);
        if (column < m - 1 && labeledGrid[row][column + 1] == 0 && grid[row][column + 1].equals("X"))
            label(row, column + 1, value);
    }
    
    public static int abs(int x)
    {
        if (x < 0)
            return -x;
        else
            return x;
    }
}