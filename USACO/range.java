/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: range
*/

import java.io.*;
import java.util.*;

class range {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("range.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("range.out")));
        int n = Integer.parseInt(in.readLine());
        boolean[][][] dp = new boolean[n + 1][n][n];
        for (int i = 0; i < n; i++) {
            String line = in.readLine();
            for (int j = 0; j < n; j++)
                dp[1][i][j] = (line.charAt(j) == '1');
        }
        in.close();
        for (int size = 2; size <= n; size++) {
            int count = 0;
            for (int i = 0; i <= n - size; i++)
                for (int j = 0; j <= n - size; j++) {
                    if (dp[size - 1][i][j] && dp[size - 1][i + 1][j]
                            && dp[size - 1][i][j + 1] && dp[size - 1][i + 1][j + 1]) {
                        dp[size][i][j] = true;
                        count++;
                    }
                }
            if (count > 0)
                out.println(size + " " + count);
        }
        out.close();
        System.exit(0);
    }
}
