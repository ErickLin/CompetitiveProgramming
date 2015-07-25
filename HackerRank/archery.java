import java.io.*;
import java.util.*;

public class archery {
    public static void main(String[] args) throws IOException {
        /*
        int a = (int) Math.ceil(Math.random() * 100000);
        System.out.println(a);
        for (int i = 0; i < a; i++)
            System.out.println((int) Math.ceil(Math.random() * 1000000));
        int b = (int) Math.ceil(Math.random() * 100000);
        System.out.println(b);
        for (int i = 0; i < b; i++) {
            System.out.println((int) Math.ceil(Math.random() * 1000000)
                    + " " + (int) Math.ceil(Math.random() * 1000000)
                    + " " + (int) Math.ceil(Math.random() * 1000000)
                    + " " + (int) Math.ceil(Math.random() * 1000000));
        }
        */
        Scanner in = new Scanner(System.in);
        int n = Integer.parseInt(in.next());
        int[] r = new int[n];
        for (int i = 0; i < n; i++)
            r[i] = Integer.parseInt(in.next());
        int m = Integer.parseInt(in.next());
        int[] x1 = new int[m];
        int[] y1 = new int[m];
        int[] x2 = new int[m];
        int[] y2 = new int[m];
        for (int i = 0; i < m; i++) {
            x1[i] = Integer.parseInt(in.next());
            y1[i] = Integer.parseInt(in.next());
            x2[i] = Integer.parseInt(in.next());
            y2[i] = Integer.parseInt(in.next());
        }
        in.close();
        Arrays.sort(r);
        //Prefix sum that keeps track of current number of circles
        int circleNum = 0;
        //Keeps track of number of circles within current radius equal to index
        int[] prefix = new int[1000001];
        //Loop through all integer radii
        for (int i = 1; i <= r[n - 1]; i++) {
            //If current radius = radius of current circle
            if (r[circleNum] == i) {
                circleNum++;
            }
            prefix[i] = circleNum;
        }
        for (int i = r[n - 1] + 1; i <= 1000000; i++) {
            prefix[i] = circleNum;
        }
        long count = 0;
        for (int i = 0; i < m; i++) {
            long r1t = x1[i] * x1[i] + y1[i] * y1[i];
            long r2t = x2[i] * x2[i] + y2[i] * y2[i];
            int r1, r2;
            if (r1t > r2t) {
                r1 = (int) Math.floor(Math.sqrt(r1t));
                r2 = (int) Math.ceil(Math.sqrt(r2t));
                count += prefix[r1] - prefix[r2 - 1];
            } else if (r2t > r1t) {
                r1 = (int) Math.ceil(Math.sqrt(r1t));
                r2 = (int) Math.floor(Math.sqrt(r2t));
                count += prefix[r2] - prefix[r1 - 1];
            }
        }
        System.out.println(count);
        System.exit(0);
    }
}