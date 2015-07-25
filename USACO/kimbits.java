/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: kimbits
*/

import java.io.*;
import java.util.*;

class kimbits {
    static long elem, ans;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("kimbits.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("kimbits.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int l = Integer.parseInt(line.nextToken());
        long i = Long.parseLong(line.nextToken());
        in.close();
        long[][] setSizes = getSetSizes(n, l);
        kim(n, l, i, setSizes, out);
        out.close();
        System.exit(0);
    }
    
    public static long[][] getSetSizes(int n, int l) {
        long[][] setSizes = new long[n + 1][l + 1];
        for (int j = 0; j <= l; j++)
            setSizes[0][j] = 1;
        for (int k = 1; k <= n; k++)
            for (int j = 0; j <= l; j++) {
                if (j == 0)
                    setSizes[k][j] = 1;
                else
                    setSizes[k][j] = setSizes[k - 1][j] + setSizes[k - 1][j - 1];
            }
        return setSizes;
    }
    
    public static void kim(int numBits, int numOnes, long index, long[][] setSizes, PrintWriter out) {
        if (numBits == 0) {
            out.println();
            return;
        }
        if (index <= setSizes[numBits - 1][numOnes]) {
            out.print("0");
            kim(numBits - 1, numOnes, index, setSizes, out);
        }
        else {
            out.print("1");
            kim(numBits - 1, numOnes - 1, index - setSizes[numBits - 1][numOnes], setSizes, out);
        }
    }
}
