/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: missing
*/

import java.io.*;
import java.util.*;

class missing {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("missing.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("missing.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n;
        while ((n = Integer.parseInt(line.nextToken())) != 0) {
            int p = Integer.parseInt(line.nextToken());
            int[] pages = findOthers(n, p);
            out.println(pages[0] + " " + pages[1] + " " + pages[2]);
            line = new StringTokenizer(in.readLine());
        }
        in.close();
        out.close();
        System.exit(0);
    }
    
    public static int[] findOthers(int n, int p) {
        int[] pages = new int[3];
        if (p <= n / 2) {
            if (p % 2 == 0)
                pages[0] = p - 1;
            else
                pages[0] = p + 1;
        }
        else {
            if (p % 2 == 0)
                pages[0] = p - 1;
            else
                pages[0] = p + 1;
        }
        pages[1] = n - p + 1;
        pages[2] = n - pages[0] + 1;
        Arrays.sort(pages);
        return pages;
    }
}
