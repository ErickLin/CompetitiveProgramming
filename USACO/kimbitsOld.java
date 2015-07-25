/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: kimbits
*/

import java.io.*;
import java.util.*;

class kimbitsOld {
    static int n, l;
    static long i, elem, ans;
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("kimbits.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("kimbits.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        n = Integer.parseInt(line.nextToken());
        l = Integer.parseInt(line.nextToken());
        i = Long.parseLong(line.nextToken());
        in.close();
        elem = 0;
        ans = 0;
        kim(n - 1, l, 0);
        for (int j = n - Long.toBinaryString(ans).length(); j > 0; j--)
            out.print(0);
        out.println(Long.toBinaryString(ans));
        out.close();
        System.exit(0);
    }
    
    public static void kim(int pos, int remaining, long bits) {
        if (elem >= i)
            return;
        if (pos == 0) {
            elem++;
            /*
            for (int k = n - 1; k >= 0; k--)
                System.out.print(newBits[k] ? 1 : 0);
            System.out.println();
            */
            if (elem >= i) {
                ans = bits;
                return;
            }
            if (remaining > 0) {
                bits |= (1 << pos);
                elem++;
                /*
                for (int k = n - 1; k >= 0; k--)
                    System.out.print(newBits[k] ? 1 : 0);
                System.out.println();
                */
                if (elem >= i)
                    ans = bits;
            }
        }
        else {
            kim(pos - 1, remaining, bits);
            if (remaining > 0) {
                bits |= (1 << pos);
                kim(pos - 1, remaining - 1, bits);
            }
        }
    }
}
