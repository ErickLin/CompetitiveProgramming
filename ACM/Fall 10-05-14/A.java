package Fall_10_05_14;

import java.io.*;
import java.util.*;

public class A {
    public static void main(String[] args) throws IOException {
        //System.out.println("5000 10000");
        //for (int i = 0; i < 5000; i++)
        //    System.out.println((int)(Math.random() * 5000) + " " + (int)(Math.random() * 10000));
        //System.out.println("0 0");
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n;
        while ((n = Integer.parseInt(line.nextToken())) != 0) {
            int m = (int) (Double.parseDouble(line.nextToken()) * 100);
            int[] c = new int[n];
            int[] p = new int[n];
            for (int i = 0; i < n; i++) {
                line = new StringTokenizer(in.readLine());
                c[i] = Integer.parseInt(line.nextToken());
                p[i] = (int) (Double.parseDouble(line.nextToken()) * 100);
            }
            //dp array that keeps max calories based on money used
            int[] maxCal = new int[m + 1];
            for (int i = 0; i < n; i++)
                //money position
                for (int j = 0; j <= m - p[i]; j++) {
                    if (j == 0 || maxCal[j] > 0)
                        if (maxCal[j + p[i]] < maxCal[j] + c[i])
                            maxCal[j + p[i]] = maxCal[j] + c[i];
                }
            int ans = 0;
            for (int j = 0; j <= m; j++) {
                if (maxCal[j] > ans)
                    ans = maxCal[j];
            }
            System.out.println(ans);
            line = new StringTokenizer(in.readLine());
        }
        in.close();
        System.exit(0);
    }
}
