/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: fence9
*/

import java.io.*;
import java.util.*;

class fence9 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("fence9.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence9.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        int p = Integer.parseInt(line.nextToken());
        in.close();
        int a2 = m * p;
        int b = 0;
        if (n == 0) {
            b += m;
        } else {
            b += euclid(n, m);
        }
        if (n == p) {
            b += m;
        } else {
            b += euclid(Math.abs(p - n), m);
        }
        b += p;
        //Pick's theorem
        out.println((int) (a2 / 2 - b / 2 + 1));
        out.close();
        System.exit(0);
    }

    public static int euclid(int k, int m) {
        while (k != m) {
            if (k > m) {
                k -= m;
            } else {
                m -= k;
            }
        }
        return k;
    }
}
