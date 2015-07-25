import java.io.*;
import java.util.*;

public class superhero2 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(line.nextToken());
            int m = Integer.parseInt(line.nextToken());
            int[][] p = new int[n][m];
            for (int level = 0; level < n; level++) {
                line = new StringTokenizer(in.readLine());
                for (int enemy = 0; enemy < m; enemy++) {
                    int health = Integer.parseInt(line.nextToken());
                    p[level][enemy] = health;
                }
            }
            int[][] b = new int[n][m];
            for (int level = 0; level < n; level++) {
                line = new StringTokenizer(in.readLine());
                for (int enemy = 0; enemy < m; enemy++) {
                    int bullets = Integer.parseInt(line.nextToken());
                    b[level][enemy] = bullets;
                }
            }
            //dp array by level that stores minimum number of bullets needed to beat that level
            int[] dp = new int[n];
            for (int j = 0; j < n; j++)
                dp[j] = Integer.MAX_VALUE;
            for (int enemy = 0; enemy < m; enemy++)
                if (dp[n - 1] > p[n - 1][enemy])
                    dp[n - 1] = p[n - 1][enemy];
            for (int level = n - 2; level >= 0; level--) {
                for (int enemy = 0; enemy < m; enemy++) {
                    if (dp[level] > Math.max(p[level][enemy], dp[level + 1] + p[level][enemy] - b[level][enemy]))
                        dp[level] = Math.max(p[level][enemy], dp[level + 1] + p[level][enemy] - b[level][enemy]);
                }
            }
            System.out.println(dp[0]);
        }
        in.close();
        System.exit(0);
    }
}
