package hackerrank;

import java.io.*;
import java.util.*;
import java.math.*;

/**
 * 
 *
 * @author Erick Lin
 */
public class lovers {
    static final int DIV = 100003;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        long t = Long.parseLong(in.readLine());
        for (int i = 0; i < t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            long _n = Long.parseLong(line.nextToken());
            long _k = Long.parseLong(line.nextToken());
            System.out.println(combinations(_n - _k + 1, _k));
        }
    }
    
    public static int combinations(long n, long k) {
        if (n < k)
            return 0;
        if (k > n / 2)
            return combinations(n, n - k);
        long num = 1;
        long denom = 1;
        for (long i = 0; i < k; i++) {
            num = (num * (n - i)) % DIV;
            denom = (denom * (i + 1)) % DIV;
        }
        //System.out.println(num + " " + BigInteger.valueOf(denom).modInverse(BigInteger.valueOf(DIV)));
        if (denom % DIV == 0)
            return (int) num;
        else
            return (int) ((num * BigInteger.valueOf(denom).modInverse(BigInteger.valueOf(DIV)).intValue()) % DIV);
    }
}