/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: haybales
*/
import java.io.*;
import java.util.*;

class haybales
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("haybales.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("haybales.out")));
        int numPiles = Integer.parseInt(in.readLine());
        int[] heights = new int[numPiles];
        int totalHeight = 0;
        for (int i = 0; i < numPiles; i++)
        {
            heights[i] = Integer.parseInt(in.readLine());
            totalHeight += heights[i];
        }
        in.close();
        int avgHeight = totalHeight / numPiles;
        int diffIntegral = 0;
        for (int i = 0; i < numPiles; i++)
        {
            diffIntegral += Math.abs(heights[i] - avgHeight);
        }
        out.println(diffIntegral / 2);
        out.close();
        System.exit(0);
    }
}