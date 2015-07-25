/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: cowjog
*/

import java.io.*;
import java.util.*;

class cowjog {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cowjog.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowjog.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int t = Integer.parseInt(line.nextToken());
        int[] start = new int[n];
        int[] speed = new int[n];
        for (int i = 0; i < n; i++) {
            line = new StringTokenizer(in.readLine());
            start[i] = Integer.parseInt(line.nextToken());
            speed[i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        long[] end = new long[n];
        for (int i = 0; i < n; i++) {
            end[i] = (long) start[i] + (long) t * (long) speed[i];
            System.out.println(end[i]);
        }
        int count = 1;
        long currentPos = end[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (end[i] < currentPos) {
                count++;
                currentPos = end[i];
            }
        }
        System.out.println(count);
        out.println(count);
        out.close();
        System.exit(0);
    }
}
