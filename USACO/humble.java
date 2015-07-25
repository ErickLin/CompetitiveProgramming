/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: humble
*/

import java.io.*;
import java.util.*;

class humble {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("humble.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("humble.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int k = Integer.parseInt(line.nextToken());
        int n = Integer.parseInt(line.nextToken());
        int[] primes = new int[k];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < k; i++)
            primes[i] = Integer.parseInt(line.nextToken());
        in.close();
        ArrayList<Long> comps = new ArrayList<Long>(n + 1);
        comps.add((long)1);
        int[] currentL = new int[k];
        for (int i = 0; i < k; i++)
            currentL[i] = 0;
        for (int i = 1; i <= n; i++) {
            long next = (long)(Math.pow(2, 31));
            for (int j = 0; j < k; j++) {
                for (int l = currentL[j]; l < i; l++) {
                    long num = (long)(primes[j] * comps.get(l));
                    if (num > comps.get(i - 1)) {
                        if (num < next) {
                            next = num;
                        }
                        currentL[j] = l;
                        break;
                    }
                }
            }
            comps.add(next);
        }
        //System.out.println(comps);
        out.println(comps.get(n));
        out.close();
        System.exit(0);
    }
    
}
