/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: bookshelf
*/
import java.io.*;
import java.util.*;

class bookshelf
{
    static final int INF = 99999999;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("bookshelf.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("bookshelf.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int w = Integer.parseInt(line.nextToken());
        int[] hts = new int[n + 1];
        int[] wids = new int[n + 1];
        //minimum height of first i books
        int[] dp = new int[n + 1];
        Arrays.fill(dp, INF);
        dp[0] = 0;
        //number of books placed in total
        for (int i = 1; i <= n; i++)
        {
            line = new StringTokenizer(in.readLine());
            hts[i] = Integer.parseInt(line.nextToken());
            wids[i] = Integer.parseInt(line.nextToken());
            int widSum = 0;
            int htMax = 0;
            //number of books placed on top shelf
            for (int j = i; j > 0 && widSum < w; j--)
            {
                widSum += wids[j];
                if (hts[j] > htMax)
                    htMax = hts[j];
                if (widSum <= w && htMax + dp[j - 1] < dp[i])
                    //height of books on top shelf + height of remaining books
                    dp[i] = htMax + dp[j - 1];
            }
        }
        in.close();
        out.println(dp[n]);
        out.close();
        System.exit(0);
    }
}