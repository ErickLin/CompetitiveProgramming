/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: rockers
*/

import java.io.*;
import java.util.*;

class rockers {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("rockers.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("rockers.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int t = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        int[] lens = new int[n];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            lens[i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        int max = 0;
        //number of disks used, time used up on current disk, current song index
        int[][][] dp = new int[m + 1][t + 1][n + 1];
        for (int song = 0; song <= n; song++)
            dp[0][0][song] = 0;
        for (int disk = 1; disk <= m; disk++)
            for (int timeUsed = 1; timeUsed <= t; timeUsed++)
                for (int song = 0; song <= n; song++)
                    dp[disk][timeUsed][song] = -1;
        for (int disk = 0; disk < m; disk++)
            for (int timeUsed = 0; timeUsed <= t; timeUsed++)
                for (int song = 0; song <= n; song++) {
                    if (dp[disk][timeUsed][song] > max)
                        max = dp[disk][timeUsed][song];
                    if (dp[disk][timeUsed][song] != -1) {
                        System.out.println(disk + " " + timeUsed + " " + song + " " + dp[disk][timeUsed][song]);
                        for (int nextSong = song; nextSong < n; nextSong++) {
                            if (timeUsed + lens[nextSong] <= t) {
                                if (dp[disk][timeUsed][song] + 1 > dp[disk][timeUsed + lens[nextSong]][nextSong + 1])
                                    dp[disk][timeUsed + lens[nextSong]][nextSong + 1] = dp[disk][timeUsed][song] + 1;
                                if (disk < m && timeUsed + lens[nextSong] == t
                                        && dp[disk][timeUsed][song] + 1 > dp[disk + 1][0][nextSong + 1])
                                    dp[disk + 1][0][nextSong + 1] = dp[disk][timeUsed][song] + 1;
                            } else if (disk < m && lens[nextSong] <= t) {
                                if (dp[disk][timeUsed][song] + 1 > dp[disk + 1][lens[nextSong]][nextSong + 1])
                                    dp[disk + 1][lens[nextSong]][nextSong + 1] = dp[disk][timeUsed][song] + 1;
                            }
                        }
                    }
                }
        out.println(max);
        out.close();
        System.exit(0);
    }
}
