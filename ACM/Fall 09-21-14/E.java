package Fall_09_21_14;

/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: E
*/

import java.io.*;
import java.util.*;

class E {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String ln = in.readLine();
        int input = 1;
        while (!ln.isEmpty()) {
            StringTokenizer line = new StringTokenizer(ln);
            long n = Long.parseLong(line.nextToken());
            long t = Long.parseLong(line.nextToken());
            long b = Long.parseLong(line.nextToken());
            t %= n;
            System.out.println("Case " + input + ": ");
            ln = in.readLine();
        }
        in.close();
        System.exit(0);
    }
}
