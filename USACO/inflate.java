/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: inflate
*/
import java.io.*;
import java.util.*;

class inflate
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("inflate.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("inflate.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int m = Integer.parseInt(line.nextToken());
        int n = Integer.parseInt(line.nextToken());
        int[] pts = new int[n];
        int[] mins = new int[n];
        for (int i = 0; i < n; i++)
        {
            line = new StringTokenizer(in.readLine());
            pts[i] = Integer.parseInt(line.nextToken());
            mins[i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        int[] opt = new int[m + 1];
        for (int i = 0; i < n; i++)
            for (int t = mins[i]; t <= m; t++)
                if (opt[t - mins[i]] + pts[i] > opt[t])
                    opt[t] = opt[t - mins[i]] + pts[i];
        out.println(opt[m]);
        out.close();
        System.exit(0);
    }
}