/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: marathon
*/

import java.io.*;
import java.util.*;

class marathon {
    static int n, k, dist;
    static int[][] dists;
    static int[][][] dp;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("marathon.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("marathon.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        n = Integer.parseInt(line.nextToken());
        k = Integer.parseInt(line.nextToken());
        int[] x = new int[n];
        int[] y = new int[n];
        dists = new int[n][n];
        for (int i = 0; i < n; i++) {
            line = new StringTokenizer(in.readLine());
            x[i] = Integer.parseInt(line.nextToken());
            y[i] = Integer.parseInt(line.nextToken());
            for (int j = 0; j <= i; j++) {
                dists[i][j] = Math.abs(x[i] - x[j]) + Math.abs(y[i] - y[j]);
                dists[j][i] = Math.abs(x[i] - x[j]) + Math.abs(y[i] - y[j]);
            }
        }
        in.close();
        dist = 0;
        for (int i = 1; i < n; i++)
            dist += Math.abs(x[i] - x[i - 1]) + Math.abs(y[i] - y[i - 1]);
        dp = new int[n][k + 1][n];
        /*
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= k; j++)
                for (int m = 0; m < n; m++)
                    dp[i][j][m] = Integer.MAX_VALUE;
        */
        gen(1, 0, 0, 0);
        out.println(dist);
        out.close();
        System.exit(0);
    }
    
    public static void gen(int pos, int numUsed, int prev, int currentDist) {
        if (pos == n - 1) {
            currentDist += dists[prev][pos];
            if (currentDist < dist)
                dist = currentDist;
            return;
        }
        if (dp[pos][numUsed][prev] == 0 || currentDist < dp[pos][numUsed][prev])
            dp[pos][numUsed][prev] = currentDist;
        else
            return;
        //don't skip checkpoint at pos
        gen(pos + 1, numUsed, pos, currentDist + dists[prev][pos]);
        if (numUsed < k) {
            //skip checkpoint at pos
            gen(pos + 1, numUsed + 1, prev, currentDist);
        }
    }
}
