/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: islands
*/
import java.io.*;
import java.util.*;

class islands
{
    static int n, maxIslands;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("islands.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("islands.out")));
        n = Integer.parseInt(in.readLine());
        int[] heights = new int[n];
        ArrayList<Integer> sortedHeights = new ArrayList<Integer>();
        for (int i = 0; i < n; i++)
        {
            heights[i] = Integer.parseInt(in.readLine());
            if (!sortedHeights.contains(heights[i]))
                sortedHeights.add(heights[i]);
        }
        in.close();
        Collections.sort(sortedHeights);
        maxIslands = 0;
        for (int h = 0; h < sortedHeights.size(); h++)
        {
            int waterHeight = sortedHeights.get(h);
            int lakes = 0;
            for (int i = 0; i < n - 1; i++)
                if (heights[i] <= waterHeight && heights[i + 1] > waterHeight)
                    lakes++;
            //if the ends are submerged
            if (heights[n - 1] <= waterHeight)
                lakes++;
            int islands = lakes + 1;
            if (heights[0] <= waterHeight)
                islands--;
            if (heights[n - 1] <= waterHeight)
                islands--;
            if (islands > maxIslands)
                maxIslands = islands;
        }
        out.println(maxIslands);
        out.close();
        System.exit(0);
    }
}