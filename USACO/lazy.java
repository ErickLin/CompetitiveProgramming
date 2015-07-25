/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: lazy
*/
import java.io.*;
import java.util.*;

class lazy
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("lazy.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lazy.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int side = Integer.parseInt(line.nextToken());
        int maxSteps = Integer.parseInt(line.nextToken());
        int[][] grass = new int[side][side];
        for (int row = 0; row < side; row++)
        {
            line = new StringTokenizer(in.readLine());
            for (int col = 0; col < side; col++)
            {
                grass[row][col] = Integer.parseInt(line.nextToken());
            }
        }
        in.close();
        //amount of reachable grass
        int[][] grassRange = new int[side][side];
        //amount of grass Bessy can reach from the origin
        grassRange[0][0] = 0;
        for (int row = 0; row <= maxSteps && row < side; row++)
        {
            for (int col = 0; col <= maxSteps - row && col < side; col++)
            {
                grassRange[0][0] += grass[row][col];
                //System.out.print(grass[row][col] + " ");
            }
            //System.out.println();
        }
        int max = grassRange[0][0];
        for (int row = 0; row < side; row++)
        {
            if (row != 0)
            {
                //move grazing area down by 1
                //borrow from the value 1 row up
                grassRange[row][0] = grassRange[row - 1][0];
                //"dCol" = distance from column 0
                //System.out.print("row: " + row + " " + grassRange[row][0]);
                for (int dCol = 0; dCol <= maxSteps && dCol < side; dCol++)
                {
                    int dRow = maxSteps - dCol;
                    if (row - (dRow) - 1 >= 0)
                    {
                        //System.out.print("-" + grass[row - (dRow) - 1][dCol]);
                        grassRange[row][0] -= grass[row - (dRow) - 1][dCol];
                    }
                    if (row + (dRow) < side)
                    {
                        //System.out.print("+" + grass[row + (dRow)][dCol]);
                        grassRange[row][0] += grass[row + (dRow)][dCol];
                    }
                }
                //System.out.println();
            }
            if (grassRange[row][0] > max)
                max = grassRange[row][0];
            //move grazing area to the right
            for (int col = 1; col < side; col++)
            {
                //borrow from the value 1 row to the left
                grassRange[row][col] = grassRange[row][col - 1];
                //"dRow" = distance from current row
                //System.out.print("row: " + row + " col: " + col + " " + grassRange[row][0]);
                for (int dRow = 0; dRow <= maxSteps; dRow++)
                {
                    int dCol = maxSteps - dRow;
                    if (row - dRow >= 0 && col - dCol - 1 >= 0)
                    {
                        //System.out.print("-" + grass[row - dRow][col - (dCol) - 1]);
                        grassRange[row][col] -= grass[row - dRow][col - (dCol) - 1];
                    }
                    if (row - dRow >= 0 && col + dCol < side)
                    {
                        //System.out.print("+" + grass[row - dRow][col + (dCol)]);
                        grassRange[row][col] += grass[row - dRow][col + (dCol)];
                    }
                    //automatically repeats when dRow = 0
                    if (dRow != 0)
                    {
                        if (row + dRow < side && col - dCol - 1 >= 0)
                        {
                            //System.out.print("-" + grass[row + dRow][col - (dCol) - 1]);
                            grassRange[row][col] -= grass[row + dRow][col - (dCol) - 1];
                        }
                        if (row + dRow < side && col + dCol < side)
                        {
                            //System.out.print("+" + grass[row + dRow][col + (dCol)]);
                            grassRange[row][col] += grass[row + dRow][col + (dCol)];
                        }
                    }
                }
                //System.out.println();
                if (grassRange[row][col] > max)
                    max = grassRange[row][col];
            }
        }
        /*for (int row = 0; row < side; row++)
        {
            for (int col = 0; col < side; col++)
                System.out.print(grassRange[row][col] + " ");
            System.out.println();
        }*/
        out.println(max);
        out.close();
        System.exit(0);
    }
}