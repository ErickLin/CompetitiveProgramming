/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: stamps
*/

import java.io.*;
import java.util.*;

class stamps {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("stamps.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("stamps.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int totalStamps = Integer.parseInt(line.nextToken());
        int numVals = Integer.parseInt(line.nextToken());
        int maxVal = 0;
        line = new StringTokenizer(in.readLine());
        int[] values = new int[numVals];
        for (int i = 0; i < numVals; i++) {
            if (!line.hasMoreTokens())
                line = new StringTokenizer(in.readLine());
            values[i] = Integer.parseInt(line.nextToken());
            if (values[i] > maxVal)
                maxVal = values[i];
        }
        in.close();
        //state function that keeps track of minimum number of stamps needed to
        //attain price in brackets
        int dp[] = new int[totalStamps * maxVal + 1];
        dp[0] = 0;
        for (int p = 1; p < dp.length; p++)
            dp[p] = totalStamps + 1;
        //O(totalStamps^2 * maxVal * numVals)
        for (int p = 0; p < dp.length; p++)
            //on a currently attainable price
            if (dp[p] <= totalStamps)
                for (int i = 0; i < numVals; i++)
                    if (p + values[i] < dp.length && dp[p] + 1 < dp[p + values[i]])
                        dp[p + values[i]] = dp[p] + 1;
        for (int p = 1; p <= totalStamps * maxVal; p++) {
            if (dp[p] >= totalStamps + 1) {
                out.println(p - 1);
                break;
            }
            if (p == totalStamps * maxVal)
                out.println(p);
        }
        out.close();
        System.exit(0);
    }
}
