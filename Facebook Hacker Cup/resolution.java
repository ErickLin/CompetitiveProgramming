/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: resolution
*/

import java.io.*;
import java.util.*;

class resolution {
    static int gp, gc, gf, n;
    static int[] p, c, f;
    static boolean found;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("new_years_resolution.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("resolution.out")));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            gp = Integer.parseInt(line.nextToken());
            gc = Integer.parseInt(line.nextToken());
            gf = Integer.parseInt(line.nextToken());
            n = Integer.parseInt(in.readLine());
            p = new int[n];
            c = new int[n];
            f = new int[n];
            for (int j = 0; j < n; j++) {
                line = new StringTokenizer(in.readLine());
                p[j] = Integer.parseInt(line.nextToken());
                c[j] = Integer.parseInt(line.nextToken());
                f[j] = Integer.parseInt(line.nextToken());
            }
            found = false;
            recurse(0, 0, 0, 0);
            out.println("Case #" + i + ": " + (found ? "yes" : "no"));
        }
        in.close();
        out.close();
        System.exit(0);
    }
    
    public static void recurse(int level, int cp, int cc, int cf) {
        if (found || cp > gp || cc > gc || cf > gf)
            return;
        if (cp == gp && cc == gc && cf == gf)
            found = true;
        else if (level < n) {
            recurse(level + 1, cp + p[level], cc + c[level], cf + f[level]);
            recurse(level + 1, cp, cc, cf);
        }
    }
}
