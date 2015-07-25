package hackerearth;

import java.io.*;
import java.util.*;

class beetles {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(line.nextToken());
            int a = Integer.parseInt(line.nextToken());
            int b = Integer.parseInt(line.nextToken());
            int c = Integer.parseInt(line.nextToken());
            int[] p = new int[n];
            int[] q = new int[n];
            int latest = 0;
            for (int j = 0; j < n; j++) {
                line = new StringTokenizer(in.readLine());
                p[j] = Integer.parseInt(line.nextToken());
                q[j] = Integer.parseInt(line.nextToken());
                if (q[j] > latest)
                    latest = q[j];
            }
            int max = 0;
            for (int s = 0; s <= latest; s++) {
                int sum = 0;
                for (int j = 0; j < n; j++) {
                    if (s < p[j])
                        sum += a;
                    else if (s >= p[j] && s <= q[j])
                        sum += b;
                    else
                        sum += c;
                }
                if (sum > max)
                    max = sum;
            }
            System.out.println(max);
        }
        in.close();
        System.exit(0);
    }
}
