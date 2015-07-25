/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: job
*/

import java.io.*;
import java.util.*;

class job {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("job.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("job.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int m1 = Integer.parseInt(line.nextToken());
        int m2 = Integer.parseInt(line.nextToken());
        int[] a = new int[m1];
        int[] b = new int[m2];
        PriorityQueue<Integer> qA = new PriorityQueue<Integer>();
        PriorityQueue<Integer> qB = new PriorityQueue<Integer>();
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < m1; i++) {
            a[i] = Integer.parseInt(line.nextToken());
            for (int j = 1; j <= 1000; j++)
                qA.add(a[i] * j);
        }
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < m2; i++) {
            b[i] = Integer.parseInt(line.nextToken());
            for (int j = 1; j <= 1000; j++)
                qB.add(b[i] * j);
        }
        in.close();
        int[] scheduleA = new int[n];
        int[] scheduleB = new int[n];
        for (int i = 0; i < n; i++) {
            scheduleA[i] = qA.poll();
            scheduleB[i] = qB.poll();
        }
        int max = 0;
        for (int i = 0; i < n; i++) {
            max = Math.max(max, scheduleA[i] + scheduleB[n - 1 - i]);
        }
        out.println(scheduleA[n - 1] + " " + max);
        out.close();
        System.exit(0);
    }
}
